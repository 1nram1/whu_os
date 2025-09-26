// kernel/sleeplock.c

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sleeplock.h"

void
initsleeplock(struct sleeplock *lk, char *name)
{
  initlock(&lk->lk, "sleep lock");
  lk->name = name;
  lk->locked = 0;
  lk->pid = 0;
}

// NOTE: This is a temporary, simplified implementation for the early boot phase.
// The real implementation will use sleep() and wakeup().
void
acquiresleep(struct sleeplock *lk)
{
  acquire(&lk->lk);
  while (lk->locked) {
    // In a real scheduler, we would sleep here.
    // For now, we spin, similar to a spinlock.
  }
  lk->locked = 1;
  // lk->pid = myproc()->pid; // myproc() is not fully implemented yet
  release(&lk->lk);
}

// NOTE: This is a temporary, simplified implementation.
void
releasesleep(struct sleeplock *lk)
{
  acquire(&lk->lk);
  lk->locked = 0;
  lk->pid = 0;
  // In a real scheduler, we would wakeup() processes waiting on this lock.
  release(&lk->lk);
}