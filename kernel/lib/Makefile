CC := /home/ramtin/x86_64-elf-7.5.0-Linux-x86_64/bin/x86_64-elf-gcc
AR := /home/ramtin/x86_64-elf-7.5.0-Linux-x86_64/bin/x86_64-elf-ar
CFLAGS := -ffreestanding -m32 -nostdlib -g -I.
SRC := string.cpp debug.cpp
OBJ := $(SRC:.cpp=.o)
LIB := libmoyai.a

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIB)

.PHONY: all clean

