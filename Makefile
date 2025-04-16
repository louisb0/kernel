CC = i686-elf-gcc
CXX = i686-elf-g++
AS = i686-elf-as
LD = i686-elf-gcc

CFLAGS = -ffreestanding -O2 -Wall -Wextra
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -MMD -MP
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
ISO_DIR = $(BUILD_DIR)/isodir

KERNEL = $(BIN_DIR)/kernel.bin
ISO = $(BIN_DIR)/kernel.iso
BOOT_OBJ = $(OBJ_DIR)/boot.o

CPP_SRCS = $(shell find src/ -name '*.cpp')
CPP_OBJS = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SRCS))
DEPS = $(CPP_OBJS:.o=.d)

all: build

run: build
	qemu-system-i386 -cdrom $(ISO)

build: $(ISO)

$(ISO): $(KERNEL) grub.cfg | $(ISO_DIR)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL) $(ISO_DIR)/boot/
	cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) $(ISO_DIR)

$(KERNEL): $(BOOT_OBJ) $(CPP_OBJS) | $(BIN_DIR)
	$(LD) $(LDFLAGS) -o $@ $^

$(BOOT_OBJ): boot.s | $(OBJ_DIR)
	$(AS) $< -o $@

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -Iinclude/ -c $< -o $@

$(OBJ_DIR) $(BIN_DIR) $(ISO_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) compile_commands.json

.PHONY: all build run clean

-include $(DEPS)
