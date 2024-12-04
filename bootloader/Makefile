ASM := nasm
STAGE1_SRC := stage1.asm
STAGE1_BIN := stage1.bin

all: $(STAGE1_BIN)

$(STAGE1_BIN): $(STAGE1_SRC)
	$(ASM) -f bin $(STAGE1_SRC) -o $(STAGE1_BIN)

clean:
	rm -f $(STAGE1_BIN)

.PHONY: all clean
