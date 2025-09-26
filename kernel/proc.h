// kernel/proc.h

// Per-CPU state.
struct cpu {
  int id; // For now, just a placeholder
};

extern struct cpu cpus[NCPU];