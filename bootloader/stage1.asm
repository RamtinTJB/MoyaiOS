org           0         ; BIOS loads the bootloader at address 0x0000:0x7c00
                        ; We'll load the address into segment registers later later

bits 16                 ; When system starts, it's in real mode (16-bit) so the
                        ; first stage bootloader has to be compiled in this mode

.start:
  cli                   ; Disable interrupts
  mov ax, 0x07C0        ; The address to which the bootloader is loaded
                        ; Refer to the comment at the top of file

  mov ds, ax            ; Data Segment
  mov es, ax            ; Extra Segment
  mov fs, ax        
  mov gs, ax

  mov ax, 0x0000        ; Setup the stack pointer
  mov ss, ax            ; Stack Segment
  mov sp, 0xFFFF        ; Stack Pointer (at the end of the segment since it grows down) 0x0000:0xFFFF
  sti                   ; Re-enable interrupts

  mov [BootDrive], dl   ; store the disk number we booted from
                        ; usually 0 for floppy, 0x80 for hard drive
  mov si, message
  call .print_string

; Resets the fixed disk controller and driver
; It forces recalibration of the read/write head
.Reset:
  mov ah, 0             ; reset drive command
  mov dl, [BootDrive]   ; drive number (refer to line 7)
  int 0x13              ; BIOS drive interrupt (refer to documentation)
  jc .Reset             ; CF is set on error, we can just try again

  mov ax, 0x0050        ; load stage 2 at segment 0x0050
  mov es, ax
  xor bx, bx            ; offset 0 -> 0x0050:0000

  mov ah, 0x02          ; read from drive command
  mov al, 1             ; number of sectors to read (1 for now)
  mov ch, 0             ; low 8 bits of cylinder number
  mov cl, 2             ; sector number (1-indexed)
  mov dh, 0             ; head number
  mov dl, [BootDrive]   ; drive number
  int 0x13              ; BIOS drive interrupt
  jc .DiskError         ; CF will be set in case of error when reading from drive

  mov si, jump_msg
  call .print_string

  push WORD 0x0050
  push WORD 0x0000
  retf                   ; Far return to the address that's on the stack: 0x0050:0x0000
                         ; This will jump to Stage 2

; In case of disk error we just print an error message and loop forever
; At least for now. probably should have more robust error handling :)
.DiskError:
  mov si, disk_error_msg
  call .print_string
  jmp $

%include "utils.asm"    ; .print_string routine is defined here

; String messages and variables
message db 'Loading Stage 2 Bootloader', 0
jump_msg db 'Jumping to stage 2', 0
disk_error_msg db 'Disk read error!', 0
BootDrive db 0

times 510 - ($-$$) db 0     ; Since bytes 511 and 512 are special, we have to fill the space
                            ; in between with zeros. $ is the current line, $$ is the beginning of the code

dw 0xAA55                   ; This is the bootloader signature
