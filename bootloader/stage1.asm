org 0x7c00              ; BIOS loads the bootloader at address 0x7c00

bits 16                 ; When system starts, it's in real mode (16-bit) so the
                        ; first stage bootloader has to be compiled in this mode

.start:
  mov si, message
  call .print_string

.loop_forever:
  jmp .loop_forever

.print_string:
  .next_char:
    lodsb
    cmp al, 0
    je .done
    mov ah, 0x0E
    int 0x10
    jmp .next_char
  .done:
    ret

message db 'Loading Stage 2 Bootloader', 0

times 510 - ($-$$) db 0     ; Since bytes 511 and 512 are special, we have to fill the space
                            ; in between with zeros. $ is the current line, $$ is the beginning of the code

dw 0xAA55                   ; This is the bootloader signature
