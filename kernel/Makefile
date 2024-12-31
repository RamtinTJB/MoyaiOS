CC := /home/ramtin/x86_64-elf-7.5.0-Linux-x86_64/bin/x86_64-elf-gcc
LD := /home/ramtin/x86_64-elf-7.5.0-Linux-x86_64/bin/x86_64-elf-ld
CFLAGS := -ffreestanding -m32 -nostdlib -g -Ilib
LDFLAGS := -m elf_i386 -T linker.ld --oformat binary
LIB := lib/libmoyai.a
LIB_DIR := lib
SRC := kernel.cpp vga.cpp gdt.cpp idt.cpp hw_interface.cpp exceptions.cpp
OBJ := $(SRC:.cpp=.o)
BIN := kernel.bin

all: $(BIN)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ) $(LIB)
	$(LD) $(LDFLAGS) $^ $(LIB) -o $@

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -f $(OBJ) $(BIN)

.PHONY: all clean
