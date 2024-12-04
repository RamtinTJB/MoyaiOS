BOOTLOADER_DIR := bootloader
DISK_IMG := moyai.img
STAGE1_BIN := $(BOOTLOADER_DIR)/stage1.bin
QEMU := qemu-system-x86_64

all: $(DISK_IMG)

bootloader:
	$(MAKE) -C $(BOOTLOADER_DIR)

$(DISK_IMG): bootloader
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=2880
	dd if=$(STAGE1_BIN) of=$(DISK_IMG) bs=512 count=1 conv=notrunc

run:
	$(QEMU) $(DISK_IMG)

clean:
	$(MAKE) -C $(BOOTLOADER_DIR) clean

.PHONY: all bootloader clean
