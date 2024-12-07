BOOTLOADER_DIR := bootloader
DISK_IMG := moyai.img
STAGE1_BIN := $(BOOTLOADER_DIR)/stage1.bin
STAGE2_BIN := $(BOOTLOADER_DIR)/stage2.bin
QEMU := qemu-system-x86_64

all: $(DISK_IMG)

bootloader:
	$(MAKE) -C $(BOOTLOADER_DIR)

$(DISK_IMG): bootloader
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=2880
	dd if=$(STAGE1_BIN) of=$(DISK_IMG) bs=512 count=1 conv=notrunc
	dd if=$(STAGE2_BIN) of=$(DISK_IMG) bs=512 seek=1 conv=notrunc

run:
	$(QEMU) -debugcon stdio -fda $(DISK_IMG)

clean:
	$(MAKE) -C $(BOOTLOADER_DIR) clean
	rm -f $(DISK_IMG)

.PHONY: all bootloader clean
