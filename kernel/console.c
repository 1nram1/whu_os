// kernel/console.c

#include "types.h"
#include "defs.h"

volatile int panicking = 0;

void
consputc(int c)
{
  uartputc_sync(c);
}

void
consoleinit(void)
{
  uartinit();
}

void
panic(char *s)
{
  printf("panic: ");
  printf(s);
  printf("\n");
  for(;;)
    ;
}