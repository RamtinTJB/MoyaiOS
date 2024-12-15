; Enable A20 address line to access 4GB of memory instead of 4MB

bits 16

; Enables the A20 line through the keyboard controller
EnableA20:
  cli
  push ax
  mov al, 0xdd            ; Keyboard controller command to enable A20 address line
  out 0x64, al            ; Keyboard controller I/O port (0x64)
  pop ax
  sti
  ret
