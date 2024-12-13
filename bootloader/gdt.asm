bits 16

setup_GDT:
  cli
  pusha
  lgdt  [toc]         ; Loads the GDTR register. This register holds the size and
                      ; the address of the Global Descriptor Table
                      ; In 32-bit mode, the first 16 bits (0-15) are the size
                      ; and the next 16 bits (16-31) are the offset
                      ; Look at the declaration of [toc] below
  sti
  popa
  ret

gdt_data:
  dd 0                ; The null descriptor
  dd 0

  dw 0FFFFh           ; The Code Descriptor
  dw 0
  db 0
  db 10011010b
  db 11001111b
  db 0

  dw 0FFFFh           ; The Data Descriptor
  dw 0
  db 0
  db 10010010b
  db 11001111b
  db 0

end_of_gdt:
toc:
  dw end_of_gdt - gdt_data - 1      ; Calculate the size of the GDT
  dd gdt_data                       ; The address of the beginning of the table

%define NULL_DESC 0                 ; First entry is the null descriptor  (0  byte offset)
%define CODE_DESC 0x8               ; Second entry is the code descriptor (8  byte offset)
%define DATA_DESC 0x10              ; Third entry is teh data descriptor  (16 byte offset)