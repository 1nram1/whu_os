// kernel/main.c

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

volatile static int started = 0;

// start() 在 S-mode 下跳转到这里
void
main()
{
  if(cpuid() == 0){
    consoleinit();
    printfinit();
    printf("\n");
    printf("Hello OS\n");
    printf("\n");
    // 此处将来会添加更多初始化代码, 如:
    // kinit();         // 物理页分配器
    // kvminit();       // 内核页表
    // procinit();      // 进程表
    // ...
    
    // 同步标志, 确保主 CPU 完成基础初始化
    __sync_synchronize();
    started = 1;
  } else {
    while(started == 0)
      ;
    __sync_synchronize();
    printf("hart %d starting\n", cpuid());
  }

  // 此处将来会调用 scheduler() 启动进程调度
  // 现在我们只是让它停在这里
  while(1)
    ;
}