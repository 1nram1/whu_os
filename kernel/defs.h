// 文件: kernel/defs.h
// 描述: 更新后的函数声明。

// Forward declarations to resolve dependencies
struct cpu;
struct spinlock;

// console.c
void consoleinit(void);
void consputc(int);

// printf.c
void printfinit(void);
int  printf(const char*, ...);
void panic(char*) __attribute__((noreturn));
void clear_screen(void); // <--- clear_screen 的声明移到这里

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