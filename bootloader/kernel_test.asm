bits 32
org 0x100000

kernel_main:
  %define VIDMEM 0xB8000
  mov edi, VIDMEM
  mov [edi], byte 'B'
  mov [edi+1], byte 0x7

hang:
  hlt
  jmp hang
