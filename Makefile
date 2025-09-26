# Makefile

# riscv64-unknown-elf- or riscv64-linux-gnu-
TOOLPREFIX = riscv64-unknown-elf-

CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)gas
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump

# QEMU
QEMU = qemu-system-riscv64
QEMUFLAGS = -machine virt -nographic -bios none -m 128M -smp 2

# C/Assembly flags
CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb
CFLAGS += -MD
CFLAGS += -mcmodel=medany
CFLAGS += -ffreestanding -fno-common -nostdlib
CFLAGS += -I.
CFLAGS += -fno-stack-protector

LDFLAGS = -z max-page-size=4096

# Kernel object files
OBJS = \
  kernel/entry.o \
  kernel/start.o \
  kernel/main.o \
  kernel/uart.o \
  kernel/printf.o \
  kernel/console.o \
  kernel/spinlock.o

# Default target
all: kernel/kernel.elf

# Linking
kernel/kernel.elf: $(OBJS) kernel/kernel.ld
	$(LD) $(LDFLAGS) -T kernel/kernel.ld -o kernel/kernel.elf $(OBJS)

# Compilation/Assembling
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

# Run in QEMU
run: all
	$(QEMU) $(QEMUFLAGS) -kernel kernel/kernel.elf

# Clean up
clean:
	rm -f kernel/*.o kernel/*.d kernel/*.elf

# Include dependency files
-include kernel/*.d