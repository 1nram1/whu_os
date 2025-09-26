# RISC-V 操作系统内核 

## 项目简介

本项目是whu_操作系统实践课程，旨在通过参考 MIT xv6-riscv 的设计，从零开始构建一个能在 QEMU 模拟器上启动的 RISC-V 操作系统内核。


## 环境要求

在编译和运行本内核前，请确保你的系统（推荐 Linux 或 WSL）中已安装以下工具：

1.  **RISC-V 交叉编译工具链**:
    * `riscv64-unknown-elf-gcc`
    * `riscv64-unknown-elf-ld`
    
2.  **QEMU 模拟器**:
    * `qemu-system-riscv64`
3.  **GNU Make**:
    * `make`

## 目录结构

```
.
├── kernel/              # 内核源代码目录
│   ├── entry.S          # 汇编入口文件
│   ├── start.c          # 机器模式启动与模式切换
│   ├── main.c           # 内核主函数 (监督者模式)
│   ├── uart.c           # UART 串口驱动
│   ├── printf.c         # 内核格式化输出
│   ├── console.c        # 控制台底层实现
│   ├── spinlock.c       # 自旋锁实现
│   ├── *.h              # 其他内核头文件
│   └── kernel.ld        # 链接器脚本
├── Makefile             # 项目编译脚本
└── README.md            # 本文档
```

## 编译与运行

### 1. 编译内核

在项目的根目录下，直接执行 `make` 命令即可编译整个内核。

```bash
make
```

该命令会调用 RISC-V 交叉编译工具链，将 `kernel/` 目录下的所有源文件编译并链接成一个名为 `kernel.elf` 的可执行文件。

### 2. 在 QEMU 中运行

编译成功后，执行 `make run` 命令来启动 QEMU 并加载你的内核。

```bash
make run
```

### 3. 清理编译文件

如果你想清除所有编译生成的目标文件 (`.o`)、依赖文件 (`.d`) 和最终的 ELF 文件，可以执行 `make clean` 命令。

```bash
make clean
```

## 预期输出

当你执行 `make run` 后，你应该会在终端看到类似如下的输出，这表明你的内核已经成功在 QEMU 的虚拟多核处理器上启动：

```
xv6 kernel is booting

hart 1 starting
```

内核在打印完这些信息后会进入一个无限循环（停机状态）。

**如何退出 QEMU**: 在当前终端下，按组合键 **`Ctrl-a`**，然后松开，再按 **`x`** 键即可退出 QEMU。

