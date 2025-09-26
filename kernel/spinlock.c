// kernel/spinlock.c

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"
#include "proc.h"
#include "spinlock.h"

void
initlock(struct spinlock *lk, char *name)
{
  lk->name = name;
  lk->locked = 0;
  lk->cpu = 0;
}

// Acquire the lock.
// Loops (spins) until the lock is acquired.
void
acquire(struct spinlock *lk)
{
  // For now, we don't have full interrupt handling or multiple CPUs,
  // so this is a simplified version. The real implementation will be
  // more complex.
  while(__sync_lock_test_and_set(&lk->locked, 1) != 0)
    ;
  __sync_synchronize();
  lk->cpu = mycpu();
}

// Release the lock.
void
release(struct spinlock *lk)
{
  lk->cpu = 0;
  __sync_synchronize();
  __sync_lock_release(&lk->locked);
}

// A dummy mycpu function for now.
// It will be properly implemented when we have a scheduler.
struct cpu*
mycpu(void) {
  return 0;
}