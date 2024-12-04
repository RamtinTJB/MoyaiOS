org 0x7c00

bits 16

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

times 510 - ($-$$) db 0

dw 0xAA55
