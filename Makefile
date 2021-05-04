CROSS_COMPILE = riscv64-unknown-elf-
CFLAGS = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -Wall

QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 1 -machine virt -bios none

GDB = ${CROSS_COMPILE}gdb
CC = ${CROSS_COMPILE}g++
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump

SRCS_ASM = \
	start.S \

SRCS_C = \
	kernel.cpp \
	uart.cpp \

OBJS = $(SRCS_ASM:.S=.o)
OBJS += $(SRCS_C:.c=.o)

.DEFAULT_GOAL := all
all: krv-os.elf

# start.o must be the first in dependency!
krv-os.elf: ${OBJS}
	${CC} $(CFLAGS) -Ttext=0x80000000 -o krv-os.elf $^
	${OBJCOPY} -O binary krv-os.elf krv-os.bin

%.o : %.cpp
	${CC} ${CFLAGS} -c -o $@ $<

%.o : %.S
	${CC} ${CFLAGS} -c -o $@ $<

run: all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel krv-os.elf

.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel krv-os.elf -s -S &
	@${GDB} krv-os.elf -q -x ../gdbinit

.PHONY : code
code: all
	@${OBJDUMP} -S krv-os.elf | less

.PHONY : clean
clean:
	rm -rf *.o *.bin *.elf

