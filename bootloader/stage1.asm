org 0x7c00              ; BIOS loads the bootloader at address 0x0000:0x7c00

bits 16                 ; When system starts, it's in real mode (16-bit) so the
                        ; first stage bootloader has to be compiled in this mode

.start:
  mov [BootDrive], dl   ; store the disk number we booted from
                        ; usually 0 for floppy, 0x80 for hard drive
  mov si, message
  call .print_string

.Reset:
  mov ah, 0             ; reset drive command
  mov dl, [BootDrive]   ; drive number (refer to line 7)
  int 0x13              ; BIOS drive interrupt
  jc .Reset

  mov ax, 0x1000        ; load stage 2 at segment 0x1000
  mov es, ax
  xor bx, bx            ; offset 0 -> 0x1000:0000

  mov ah, 0x02          ; read from drive command
  mov al, 1             ; number of sectors to read (1 for now)
  mov ch, 0             ; low 8 bits of cylinder number
  mov cl, 2             ; sector number (1-indexed)
  mov dh, 0             ; head number
  mov dl, [BootDrive]   ; drive number
  int 0x13              ; BIOS drive interrupt
  jc .DiskError         ; In case of error when reading from drive

  mov si, jump_msg
  call .print_string

  jmp 0x1000:0x0        ; Execute stage 2

.DiskError:
  mov si, disk_error_msg
  call .print_string
  jmp $

.print_string:
  .next_char:
    lodsb
    cmp al, 0
    je .done
    mov ah, 0x0E
    int 0x10
    jmp .next_char
  .done:                 ; prints new line and returns from the routine
    ; print carriage return (\r)
    mov al, 0x0D
    mov ah, 0x0E
    int 0x10
    ; print line feed (\n)
    mov al, 0x0A
    mov ah, 0x0E
    int 0x10
    ret

message db 'Loading Stage 2 Bootloader', 0
jump_msg db 'Jumping to stage 2', 0
disk_error_msg db 'Disk read error!', 0
BootDrive db 0

times 510 - ($-$$) db 0     ; Since bytes 511 and 512 are special, we have to fill the space
                            ; in between with zeros. $ is the current line, $$ is the beginning of the code

dw 0xAA55                   ; This is the bootloader signature
