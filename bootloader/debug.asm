bits 32

; Routine to print strings using into QEMU Debug Console (port 0xE9)
; Inputs:
;     - esi: string to print (has to be 0-terminated)
write_debug_pm:               ; Write to QEMU debug console in protected mode
  pusha
  .next_char_pm:
    lodsb                     ; Loads a byte from DS:ESI into AL
    cmp al, 0                 ; Check if we are at the end of the string
    je .done_pm               ; je = jump if equal (finish printing)
    mov dx, 0xE9              ; QEMU Debug Console port
    out dx, al                ; print the character to the port
    jmp .next_char_pm
  .done_pm:
    popa
    ret