# kernel/entry.S

# QEMU -kernel 会将内核加载到 0x80000000
# 并让每个 hart (CPU核心) 跳转到这里。
.section .text.entry 
.globl _entry
_entry:
    # 为 C 代码设置栈。
    # stack0 在 start.c 中定义，每个 CPU 核心有 4096 字节。
    # sp = stack0 + (hartid + 1) * 4096
    la sp, stack0
    li a0, 4096
    csrr a1, mhartid
    addi a1, a1, 1
    mul a0, a0, a1
    add sp, sp, a0

    # 跳转到 start() 函数 (在 start.c 中)
    call start

# 如果 start 返回了 (理论上不应该)，则在此处死循环。
spin:
    j spin