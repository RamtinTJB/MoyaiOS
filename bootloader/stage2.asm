bits 16

org 0x0000                ; stage 2 is loaded at 0x1000:0000

.start:
  mov ax, cs              ; cs is 0x1000 since that's the segment
                          ; where we loaded stage 2 so we need to make sure
                          ; ds (data segment) points to the same segment
  mov ds, ax
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

message db 'Stage 2 loaded!', 0
