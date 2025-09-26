// kernel/defs.h

// Forward declarations to resolve dependencies
struct cpu;
struct spinlock;

// console.c
void consoleinit(void);
void consputc(int);
void panic(char*) __attribute__((noreturn));

// printf.c
void printfinit(void);
int  printf(const char*, ...);

// spinlock.c
void acquire(struct spinlock*);
void initlock(struct spinlock*, char*);
void release(struct spinlock*);
struct cpu* mycpu(void);

// uart.c
void uartinit(void);
void uartputc_sync(int);

// riscv.h
int cpuid();