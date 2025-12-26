# AetheriaKernel

Minimal 32-bit hobby kernel with VGA text mode and interactive shell (OSDev learning project)

Written in C & NASM

> 🧊 Archived project.  
> Created as a personal OSDev learning exercise. No further development planned.

## Overview
This project was written to explore low-level OS development concepts such as
x86 protected mode, interrupt handling, and basic hardware drivers.

## Implemented Features
- Multiboot-compatible 32-bit kernel
- VGA text mode output
- IDT and IRQ handling
- PIC and PIT initialization
- Keyboard input
- Basic interactive shell
- RTC access


## Building & Running
### Requirements
- NASM
- GCC
- LD
- QEMU

### Build
```bash
make 
```
### Run
```bash
make runkernel
```
### Clean
```bash
make clean
```

## Inspiration & Resources
- [OSDev wiki](https://wiki.osdev.org/)
- [Arjun Sreedharan's blog - Kernel 101](https://arjunsreedharan.org/post/82710718100/kernels-101-lets-write-a-kernel)
- [Arjun Sreedharan's blog - Kernel 201](https://arjunsreedharan.org/post/99370248137/kernels-201-lets-write-a-kernel-with-keyboard)