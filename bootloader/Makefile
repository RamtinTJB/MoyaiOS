ASM := nasm
STAGE1_SRC := stage1.asm
STAGE2_SRC := stage2.asm
STAGE1_BIN := stage1.bin
STAGE2_BIN := stage2.bin
KERNEL_TEST_SRC := kernel_test.asm
KERNEL_TEST_BIN := kernel_test.bin

all: $(STAGE1_BIN) $(STAGE2_BIN) $(KERNEL_TEST_BIN)

$(STAGE1_BIN): $(STAGE1_SRC)
	$(ASM) -f bin $(STAGE1_SRC) -o $(STAGE1_BIN)

$(STAGE2_BIN): $(STAGE2_SRC)
	$(ASM) -f bin $(STAGE2_SRC) -o $(STAGE2_BIN)

$(KERNEL_TEST_BIN): $(KERNEL_TEST_SRC)
	$(ASM) -f bin $(KERNEL_TEST_SRC) -o $(KERNEL_TEST_BIN)

clean:
	rm -f $(STAGE1_BIN) $(STAGE2_BIN) $(KERNEL_TEST_BIN)

.PHONY: all clean
