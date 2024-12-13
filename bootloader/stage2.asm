bits 16

org 0x500               ; stage 2 is loaded at 0x0050:0000 (so linear address is 0x500)

jmp start               ; Jump past the gdt stuff to the start of stage 2

%include "gdt.asm"      ; The Global Descriptor Table

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
  call .print_string

  call setup_GDT        ; Setup the GDT
                        ; The function is located in gdt.asm and it uses the lgdt instruction

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

  cli
  hlt                   ; Halt the system

debug_message_pm db 'Entered Protected Mode!', 0