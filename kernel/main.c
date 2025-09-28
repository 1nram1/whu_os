// 文件: kernel/main.c
// 描述: 增加延迟以便观察清屏效果。

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

volatile static int started = 0;

void test_printf_basic() {
  printf("--- Running Basic Tests ---\n");
  printf("Testing integer: %d\n", 42);
  printf("Testing negative: %d\n", -123);
  printf("Testing zero: %d\n", 0);
  printf("Testing hex: 0x%x\n", 0xABC);
  printf("Testing string: %s\n", "Hello, World!");
  printf("Testing char: %c\n", 'X');
  printf("Testing pointer: %p\n", (void*)0x80000000);
  printf("Testing percent: %%\n");
  printf("Unknown format: %q\n");
  printf("\n");
}

void test_printf_edge_cases() {
  printf("--- Running Edge Case Tests ---\n");
  printf("INT_MAX: %d\n", 2147483647);
  printf("INT_MIN: %d\n", -2147483648); 
  printf("NULL string: %s\n", (char*)0);
  printf("Empty string: %s\n", "");
  printf("\n");
}


void
main()
{
  if(cpuid() == 0){
    consoleinit();
    printfinit();
    
    // --- 演示部分 ---
    printf("\nThis message will be cleared in a moment...\n");
    printf("It is used to demonstrate the clear_screen() function.\n");
    
    // 增加延迟，确保有足够时间看到这条消息
    for(volatile int i = 0; i < 25000000; i++);

    // 调用修正后的清屏功能
    clear_screen(); 
    // --- 演示部分结束 ---

    printf("whu_os kernel is booting\n");
    printf("=========================\n");
    printf("\n");
    
    test_printf_basic();
    test_printf_edge_cases();

    __sync_synchronize();
    started = 1;
  } else {
    while(started == 0)
      ;
    __sync_synchronize();
    printf("hart %d starting\n", cpuid());
  }

  while(1)
    ;
}