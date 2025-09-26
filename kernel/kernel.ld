/* kernel/kernel.ld */
OUTPUT_ARCH(riscv)
ENTRY(_entry)

/* 定义内核加载的内存地址 */
BASE_ADDRESS = 0x80000000;

SECTIONS
{
    . = BASE_ADDRESS;

    .text : {
        /* 将入口代码放在最前面 */
        KEEP(*(.text.entry))
        *(.text .text.*)
    }

    .rodata : {
        . = ALIGN(16);
        *(.rodata .rodata.*)
    }

    .data : {
        . = ALIGN(16);
        *(.data .data.*)
    }

    .bss : {
        . = ALIGN(16);
        sbss = .;
        *(.bss .bss.*)
        end = .;
    }

    /* 将栈定义在内核镜像的末尾 */
    . = ALIGN(4096);
    stack0_bottom = .;
    /*
     * 关键修改：将 NCPU 替换为具体的值 8。
     * 为 8 个 CPU 核心分配栈空间 (每个 4KB)。
     */
    . = . + 4096 * 8;
    stack0 = .;
}