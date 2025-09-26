// kernel/uart.c

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

// NS16550A UART 寄存器
#define RHR 0 // Receive Holding Register (read)
#define THR 0 // Transmit Holding Register (write)
#define IER 1 // Interrupt Enable Register
#define FCR 2 // FIFO Control Register
#define ISR 2 // Interrupt Status Register
#define LCR 3 // Line Control Register
#define LSR 5 // Line Status Register

#define Reg(reg) ((volatile unsigned char *)(UART0 + (reg)))
#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

void
uartinit(void)
{
  // 禁用中断
  WriteReg(IER, 0x00);

  // 设置波特率 38.4k
  WriteReg(LCR, 0x80); // LCR[7] = 1, 允许访问波特率设置寄存器
  WriteReg(0, 0x03);
  WriteReg(1, 0x00);

  // 设置 8-bit 字长, 1 停止位, 无校验位, 并禁用波特率设置
  WriteReg(LCR, 0x03);

  // 使能并清空 FIFO
  WriteReg(FCR, 0x07);

  // 重新使能中断 (虽然我们暂时不处理)
  WriteReg(IER, 0x01);
}

// 同步(轮询)方式发送一个字符
void
uartputc_sync(int c)
{
  // 等待 LSR_TX_IDLE 位, 表示发送硬件已准备好
  while((ReadReg(LSR) & (1 << 5)) == 0)
    ;
  WriteReg(THR, c);
}