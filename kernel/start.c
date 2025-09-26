#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

void main();
void timerinit();

// entry.S 需要为每个 CPU 准备一个栈
__attribute__ ((aligned (16))) char stack0[4096 * NCPU];

// entry.S 在机器模式下跳转到这里
void
start()
{
  // 设置 mstatus.MPP 为 Supervisor 模式, 供 mret 指令使用
  unsigned long x = r_mstatus();
  x &= ~MSTATUS_MPP_MASK;
  x |= MSTATUS_MPP_S;
  w_mstatus(x);

  // 设置 mepc 为 main 函数地址, mret 将会跳转到这里
  w_mepc((uint64)main);

  // 暂时禁用分页机制
  w_satp(0);

  // 将所有中断和异常委托给 Supervisor 模式处理
  w_medeleg(0xffff);
  w_mideleg(0xffff);
  w_sie(r_sie() | SIE_SEIE | SIE_STIE);

  // 配置物理内存保护 (PMP), 允许 S-mode 访问所有物理内存
  w_pmpaddr0(0x3fffffffffffffull);
  w_pmpcfg0(0xf);

  // 设置时钟中断
  timerinit();

  // 将每个 CPU 的 hartid 保存到 tp 寄存器, 供 cpuid() 使用
  int id = r_mhartid();
  w_tp(id);

  // 切换到 Supervisor 模式并跳转到 main()
  asm volatile("mret");
}

// 设置 M-mode 的时钟中断
void
timerinit()
{
  // M-mode 下的时钟寄存器是 memory-mapped 的
  int hart = r_mhartid();
  uint64 interval = 10000000; // ~1/10 second
  *(uint64*)CLINT_MTIMECMP(hart) = *(uint64*)CLINT_MTIME + interval;

  // 开启 M-mode 的时钟中断
  w_mie(r_mie() | MIE_MTIE);
}