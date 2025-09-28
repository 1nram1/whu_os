// 文件: kernel/console.c
// 描述: 简化后的控制台，只负责初始化和传递字符。

#include "types.h"
#include "defs.h"

// 将单个字符发送给UART
void
consputc(int c)
{
  uartputc_sync(c);
}

// 初始化控制台（实际上就是初始化UART）
void
consoleinit(void)
{
  uartinit();
}