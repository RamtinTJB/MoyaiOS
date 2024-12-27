# Debugging

Debugging an operating system, especially in its early stages is a very difficult task. This is an ongoing document of my attempts at debugging the kernel. It will grow over time as I learn new techniques and write neww debugging capabilities into the system.

### QEMU Debugging Console
If we run QEMU with the debug console activated (`-debugcon`), we can write debug messages in the `0xE9` I/O port using the `outb` instruction. The debug console is exposed to the guest operating as any other device, only through port I/O and not MMIO.

Here is how we can use this debugging technique in assembly (useful in bootloader stages):

```asm
.write_debug:
    .next_char_debug:
        lodsb
        cmp al, 0
        je .done_write_debug
        mov dx, 0xE9
        out dx, al
        jmp .next_char_debug
    .done_write_debug:
        ret
```

and then we can call it as follows:

```asm
mov si, debug_message
call .write_debug

debug_message db 'Testing QEMU Debug', 0
```

We can utilize the same functionality in the kernel as well to print debugging messages to Qemu's console. All the functions are in the `<debug.hpp>` header file. The following function are available:

```cpp
void debug_write_char(char c);
void debug_write_string(const char* str);
void debug_printf(const char* format, ...);
```

### Connecting GDB to QEMU

TODO: Write this section in details
