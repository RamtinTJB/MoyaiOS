# BIOS
A BIOS (Basic Input/Output System) is a form of firmware that's pre-installed on a computer's motherboard and runs when the system is first powered on. This is the sequence of events:
- Power-On Self-Test (POST):
  - The CPU starts executing the BIOS code at `0xFFFF0` (near the top of the memory)
  - The BIOS, resides in memory at `0xF0000` to `0xFFFFF`
  - POST checks essential hardware (CPU, RAM, ...)
- BIOS Initialization
  - Sets up basic system hardware (like video and storage controllers)
  - Configures interrupt vectors for BIOS services. Some examples:
    - `INT 0x10`: Video services (text/graphics display)
    - `INT 0x13`: Disk services. this is how we can load the second stage bootloader into memory
    - `INT 0x16`: Keyboard services (input handling)
- Boot Device Selection:
  - Reads the boot priority order from non-volatile memory
  - Selects the boot device
  - Verifies the boot signature (`0xAA55` at bytes 510-511)
  - Reads the first sector (512 bytes) of the boot device into memory at `0x7C00`
- Transfer Control:
  - Sets the instruction pointer to `0x7C00` and begins executing the first-stage bootloader
  - Leaves `DL` containing the boot device number from which the boot loader from loaded from

BIOS provides a lot of useful funcionalities through interrups. This is a pretty comprehensive documentation for these interrupts: [BIOS Interrupts](https://grandidierite.github.io/bios-interrupts/)

# First Stage Bootloader
The first stage bootloader is responsible for loading the second stage. The reason we have two stages is that the first stage has to be at most 512 bytes in size. By having two stages, we have a lot more room before jumping to the kernel code.

Doing everything necessary to activate protected mode, load kernel into memory, and handle errors would be incredibly difficult if not impossible to do in 512 bytes. That's why it's a lot easier to split the bootloader into 2 stages.

### Few notes about the the first stage bootloader
- BIOS read the first sector (512 bytes) from the bootable device into memory
- For BIOS to detect that a device is bootable, `0xAA55` has to be the 511th and 512 bytes.
- BIOS loads the bootloader at address `0x0000:0x7C00` and starts executing the code 
- Stage1 loads Stage2 into from disk into `0x0050:0x0000` and executes it

There are a lot of documentation in the source code on what each line and instruction does: [stage1](https://github.com/RamtinTJB/MoyaiOS/blob/main/bootloader/stage1.asm)

# Second Stage Bootloader
The second stage bootloader is responsible for preparing the system, enter protected mode, and run the kernel. Here is a brief description of the steps performed by stage 2:

- Transition from [Real Mode](https://wiki.osdev.org/Real_Mode) (16-bit) to [Protected Mode](https://wiki.osdev.org/Protected_Mode) (32-bit):
  - Set up the [Global Descriptor Table](https://wiki.osdev.org/Global_Descriptor_Table) to define memory segments (null, data, code)
  - Enable the [A20 Line](https://wiki.osdev.org/A20_Line) allowing access to memory beyond 1MB up to 4GB.
  - Switches the processor to protected mode by setting the appropriate bit in the `CR0` register
- Load the kernel into memory
  - Reads the kernel file from the disk (starting at sector 4) using the BIOS `int 0x13` interrupt
  - Copies the kernel into the 1MB memory location (0x100000) after activating the A20 line.
- Transfer control to the kernel by jumping to the kernel entry point (0x100000) after successfully setting up protected mode

For more detailed documentation of the process, read the source code of [stage2](https://github.com/RamtinTJB/MoyaiOS/blob/main/bootloader/stage2.asm)