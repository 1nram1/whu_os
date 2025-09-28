// 文件: kernel/uart.c
// 描述: 修正并完善 UART 驱动，使其能正确处理控制字符。

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

// QEMU 模拟的 NS16550A UART 寄存器地址偏移
// 引用自 xv6，添加了更完整的宏定义
#define RHR 0                 // Receive Holding Register (read only)
#define THR 0                 // Transmit Holding Register (write only)
#define IER 1                 // Interrupt Enable Register
#define FCR 2                 // FIFO Control Register (write only)
#define ISR 2                 // Interrupt Status Register (read only)
#define LCR 3                 // Line Control Register
#define LSR 5                 // Line Status Register

// LSR 寄存器的位定义
#define LSR_TX_IDLE (1 << 5)  // Transmit-hold-register is empty

// LCR 寄存器的位定义
#define LCR_BAUD_LATCH (1 << 7) // Special mode to set baud rate
#define LCR_EIGHT_BITS (3 << 0) // 8 bits per byte

// FCR 寄存器的位定义
#define FCR_FIFO_ENABLE (1 << 0)
#define FCR_FIFO_CLEAR (3 << 1)  // Clear both TX and RX FIFOs

#define Reg(reg) ((volatile unsigned char *)(UART0 + (reg)))
#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

// 初始化 UART 硬件
void
uartinit(void)
{
  // 禁用中断
  WriteReg(IER, 0x00);

  // 设置波特率，这是一个特殊的操作模式
  // 1. 设置 LCR 的第7位，允许访问波特率除数锁存器
  WriteReg(LCR, LCR_BAUD_LATCH);
  // 2. 设置波特率为 38.4k (除数为3)
  WriteReg(0, 0x03);
  WriteReg(1, 0x00);

  // 设置线路控制：8位数据位, 1位停止位, 无校验位。
  // 同时清除 LCR 的第7位，退出波特率设置模式。
  WriteReg(LCR, LCR_EIGHT_BITS);

  // **这是关键修复**：使能并重置 FIFO 缓冲区。
  WriteReg(FCR, FCR_FIFO_ENABLE | FCR_FIFO_CLEAR);

  // 重新使能接收中断 (虽然我们暂时不用中断，但这是好的实践)
  WriteReg(IER, 0x01);
}

// 以同步（轮询）方式发送一个字符
void
uartputc_sync(int c)
{
  // 循环等待，直到发送保持寄存器为空
  // LSR 的第5位 (LSR_TX_IDLE) 为1表示可以发送
  while((ReadReg(LSR) & LSR_TX_IDLE) == 0)
    ;
  // 将字符写入发送保持寄存器
  WriteReg(THR, c);
}