bits 16

; Routine to print strings using 0x10 BIOS interrupt
; Inputs:
;     - si: string to print (has to be 0-terminated)
.print_string:
  pusha                 ; Push all general purpose registers to stack (ax, cx, dx, bx, sp, bp, si, di)
  .next_char:
    lodsb
    cmp al, 0           ; Reached the end of the string once we hit a zero
    je .done
    mov ah, 0x0E        ; Write character in teletype mode 
    int 0x10            ; BIOS interrupt
    jmp .next_char
  .done:
    mov al, 0x0D        ; Print carriage return (\r)
    mov ah, 0x0E
    int 0x10
    mov al, 0x0A        ; Print line feed (\n)
    mov ah, 0x0E
    int 0x10

    popa                ; Pop all general purpose registers from the stack
    ret
