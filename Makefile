
BOOT_SRC = boot/boot.asm
KERNEL_SRC = kernel/kernel.c
GRAPHICS_SRC = kernel/graphics.c
PIT_SRC = kernel/pit.c
PIC_SRC = kernel/pic.c
PORTS_SRC = kernel/ports.c
IDT_SRC = kernel/idt.c
IRQ0_HANDLER_SRC = kernel/irq0_handler.asm
IRQ1_HANDLER_SRC = kernel/irq1_handler.asm
KEYBOARD_SRC = kernel/keyboard.c
SHELL_SRC = kernel/shell.c               
UTILS_SRC = kernel/utils.c
STACK_PROTECTOR = kernel/stack_protector_stub.c
LINKER_SCRIPT = linker.ld
RTC_SRC = kernel/rtc.c
EDIT_SRC = kernel/edit.c


BUILD_DIR = build


BOOT_OBJ = $(BUILD_DIR)/boot.o
KERNEL_OBJ = $(BUILD_DIR)/kernel.o
GRAPHICS_OBJ = $(BUILD_DIR)/graphics.o
PIT_OBJ = $(BUILD_DIR)/pit.o
PIC_OBJ = $(BUILD_DIR)/pic.o
PORTS_OBJ = $(BUILD_DIR)/ports.o
IDT_OBJ = $(BUILD_DIR)/idt.o
IRQ0_HANDLER_OBJ = $(BUILD_DIR)/irq0_handler.o
IRQ1_HANDLER_OBJ = $(BUILD_DIR)/irq1_handler.o
KEYBOARD_OBJ = $(BUILD_DIR)/keyboard.o
SHELL_OBJ = $(BUILD_DIR)/shell.o             
UTILS_OBJ = $(BUILD_DIR)/utils.o
STACK_PROTECTOR_OBJ = $(BUILD_DIR)/stack_protector_stub.o
RTC_OBJ = $(BUILD_DIR)/rtc.o
EDIT_OBJ = $(BUILD_DIR)/edit.o

KERNEL_BIN = $(BUILD_DIR)/kernel.bin


NASM = nasm
CC = gcc
LD = ld


CFLAGS = -m32 -ffreestanding -Wall -Wextra -nostdlib -fno-stack-protector 
NASMFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T $(LINKER_SCRIPT)


all: $(KERNEL_BIN)


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(BOOT_OBJ): $(BOOT_SRC) | $(BUILD_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

$(KERNEL_OBJ): $(KERNEL_SRC) kernel/graphics.h kernel/pit.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(GRAPHICS_OBJ): $(GRAPHICS_SRC) kernel/graphics.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(PIT_OBJ): $(PIT_SRC) kernel/pit.h kernel/ports.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(PIC_OBJ): $(PIC_SRC) kernel/pic.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(PORTS_OBJ): $(PORTS_SRC) kernel/ports.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(IDT_OBJ): $(IDT_SRC) kernel/idt.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(IRQ0_HANDLER_OBJ): $(IRQ0_HANDLER_SRC) | $(BUILD_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

$(IRQ1_HANDLER_OBJ): $(IRQ1_HANDLER_SRC) | $(BUILD_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

$(KEYBOARD_OBJ): $(KEYBOARD_SRC) kernel/keyboard.h kernel/ports.h kernel/graphics.h kernel/idt.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SHELL_OBJ): $(SHELL_SRC) kernel/shell.h kernel/graphics.h kernel/ports.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(UTILS_OBJ): $(UTILS_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(STACK_PROTECTOR_OBJ): $(STACK_PROTECTOR) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(RTC_OBJ): $(RTC_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EDIT_OBJ): $(EDIT_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(KERNEL_BIN): $(BOOT_OBJ) $(KERNEL_OBJ) $(GRAPHICS_OBJ) $(PIT_OBJ) $(PIC_OBJ) $(PORTS_OBJ) $(IDT_OBJ) \
               $(IRQ0_HANDLER_OBJ) $(IRQ1_HANDLER_OBJ) $(KEYBOARD_OBJ) $(STACK_PROTECTOR_OBJ) $(UTILS_OBJ) $(SHELL_OBJ) $(RTC_OBJ) $(EDIT_OBJ) | $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(BOOT_OBJ) $(KERNEL_OBJ) $(GRAPHICS_OBJ) $(PIT_OBJ) $(PIC_OBJ) $(PORTS_OBJ) \
	$(IDT_OBJ) $(IRQ0_HANDLER_OBJ) $(IRQ1_HANDLER_OBJ) $(KEYBOARD_OBJ) $(STACK_PROTECTOR_OBJ) $(UTILS_OBJ) $(SHELL_OBJ) $(RTC_OBJ) $(EDIT_OBJ)


runkernel: $(KERNEL_BIN)
	qemu-system-x86_64 -kernel $(KERNEL_BIN)


clean:
	rm -rf $(BUILD_DIR) $(KERNEL_BIN)

.PHONY: all clean runkernel
