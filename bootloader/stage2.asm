bits 16

org 0x0000                ; stage 2 is loaded at 0x1000:0000

.start:
  mov ax, cs              ; cs is 0x1000 since that's the segment
                          ; where we loaded stage 2 so we need to make sure
                          ; ds (data segment) points to the same segment
  mov ds, ax

  mov si, debug_message
  call .write_debug

  mov si, message
  call .print_string

.loop_forever:
  jmp .loop_forever

.write_debug:
  .next_char_debug:
    lodsb
    cmp al, 0
    je .done_debug
    mov dx, 0xE9
    out dx, al
    jmp .next_char_debug
  .done_debug:
    ret

%include "utils.asm"

message db 'Stage 2 loaded!', 0
debug_message db 'Testing QEMU Debug', 0
