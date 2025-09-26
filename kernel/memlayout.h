// kernel/memlayout.h

// QEMU 'virt' machine layout
#define UART0 0x10000000L
#define CLINT 0x2000000L
#define CLINT_MTIMECMP(hart) (CLINT + 0x4000 + 8*(hart))
#define CLINT_MTIME (CLINT + 0xBFF8)
#define KERNBASE 0x80000000L