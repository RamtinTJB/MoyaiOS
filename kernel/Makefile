CC := /home/ramtin/x86_64-elf-7.5.0-Linux-x86_64/bin/x86_64-elf-gcc
LD := /home/ramtin/x86_64-elf-7.5.0-Linux-x86_64/bin/x86_64-elf-ld
CFLAGS := -ffreestanding -m32 -nostdlib -g -Ilib
LDFLAGS := -m elf_i386 -Ttext 0x100000 --oformat binary -e kernel_main
LIB := lib/libmoyai.a
LIB_DIR := lib
SRC := kernel.cpp vga.cpp
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
