extern "C" void kernel_main() {
  asm volatile (
        "mov $0x10, %%ax\n"  // DATA_DESC (GDT index 0x10)
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        :
        :
        : "ax"

    );

  char* video_memory = (char*)0xB8000;
  video_memory[0] = 'Z';
  video_memory[1] = 0x8;

  while (1) {}
}
