bits 16

org 0x500               ; stage 2 is loaded at 0x0050:0000 (so linear address is 0x500)

jmp start               ; Jump past the gdt stuff to the start of stage 2

%include "gdt.asm"      ; The Global Descriptor Table
%include "a20.asm"

start:
  cli                   ; Disable interrupts 
  xor ax, ax            ; We set all the segment registers (except for CS) to 0
  mov ds, ax            ; Data Segment
  mov es, ax            ; Extra Segment
  mov ax, 0x9000        ; Use 0x9000 as the stack segment
  mov ss, ax            ; Stack segment
  mov sp, 0xFFFF        ; Stack grows downward to sp points to the end of it initially
  sti

  mov si, message
  call print_string

  call setup_GDT        ; Setup the GDT
                        ; The function is located in gdt.asm and it uses the lgdt instruction

  call EnableA20        ; Enable A20 address line (defined in a20.asm)

  mov ax, 0x9000
  mov es, ax
  xor bx, bx
  mov ah, 0x02
  mov al, 41             ; Number of sectors that the kernel occupy (adjust over time)
  mov ch, 0
  mov cl, 4             ; Starts from sector 4
  mov dh, 0
  mov dl, 0x80
  int 0x13
  jc .disk_error
  jmp enter_protected_mode

.disk_error:
  mov si, disk_error_msg
  call print_string
  jmp $

enter_protected_mode:
  cli                   ; Disable interrupts before entering protected mode
                        ; We don't have access to any of the BIOS interrupts in protected mode
                        ; So if an interrupt happens in protected mode, the system will triple fault
                        ; We need to disable interrupt until we program the interrupt controller

  mov eax, cr0          ; The first bit in the cr0 register determines if the system
                        ; is in protected mode. So to enter protected mode,
                        ; We can just set the first bit
  or eax, 1
  mov cr0, eax  

  jmp CODE_DESC:Stage3  ; Far jump to stage 3
                        ; CODE_DESC is defined in gdt.asm

%include "utils.asm"    ;.print_string function is defined here

message db 'Stage 2 loaded!', 0

bits 32                 ; The beginning of the protected mode
                        ; All the code from here on out is in 32-bit mode

%include "debug.asm"    ; Function to write to QEMU debug console (Port 0xE9)

Stage3:
  mov ax, DATA_DESC     ; DATA_DESC is defined in gdt.asm
  mov ds, ax            ; Data segment
  mov ss, ax            ; Stack segment
  mov es, ax            ; Extra segment
  mov esp, 90000h       ; 32-bit stack pointer

  mov esi, debug_message_pm
  call write_debug_pm

  mov esi, 0x90000
  mov edi, 0x100000
  mov ecx, 512 * 41 / 4    ; Number of sectors that kernel occupies
  rep movsd               ; Copy kernel from 0x30000 to 1MB address

  call CODE_DESC:0x100000 ; Jump to the loaded C Kernel

  cli
  hlt                   ; Halt the system

debug_message_pm db 'Entered Protected Mode!', 0x0D, 0x0A, 0
disk_error_msg db 'Error reading from disk', 0x0D, 0x0A, 0
