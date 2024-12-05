# First Stage Bootloader
The first stage bootloader is responsible for loading the second stage. The reason we have two stages is that the first stage has to be at most 512 bytes in size. By having two stages, we have a lot more room before jumping to the kernel code.

Doing everything necessary to activate protected mode, load kernel into memory, and handle errors would be incredibly difficult if not impossible to do in 512 bytes. That's why it's a lot easier to split the bootloader into 2 stages.

### Few notes about the the first stage bootloader
- BIOS read the first sector (512 bytes) from the bootable device into memory
- For BIOS to detect that a device is bootable, `0xAA55` has to be the 511th and 512 bytes.
- BIOS loads the bootloader at address `0x0000:0x7C00` and starts executing the code 
- Stage1 loads Stage2 into from disk into `0x1000:0x0000` and executes it

There are a lot of documentation in the source code on what each line and instruction does: [stage1](https://github.com/RamtinTJB/MoyaiOS/blob/main/bootloader/stage1.asm)
