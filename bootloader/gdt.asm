bits 16

setup_GDT:
  cli
  pusha
  lgdt  [toc]
  sti
  popa
  ret

gdt_data:
  dd 0                ; The null descriptor
  dd 0

  dw 0FFFFh
  dw 0
  db 0
  db 10011010b
  db 11001111b
  db 0

  dw 0FFFFh
  dw 0
  db 0
  db 10011010b
  db 11001111b
  db 0

end_of_gdt:
toc:
  dw end_of_gdt - gdt_data - 1
  dd gdt_data