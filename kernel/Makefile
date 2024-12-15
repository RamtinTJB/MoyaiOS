CC := /home/ramtin/x86_64-elf-7.5.0-Linux-x86_64/bin/x86_64-elf-gcc
LD := /home/ramtin/x86_64-elf-7.5.0-Linux-x86_64/bin/x86_64-elf-ld
CFLAGS := -ffreestanding -m32 -nostdlib -g
LDFLAGS := -m elf_i386 -Ttext 0x100000 --oformat binary -e kernel_main
SRC := kernel.cpp vga.cpp debug.cpp
OBJ := $(SRC:.cpp=.o)
BIN := kernel.bin

all: $(BIN)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean
