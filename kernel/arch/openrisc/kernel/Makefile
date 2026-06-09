#
# Makefile for the beep kernel.
#

extra-y	:= head.o vmbeep.lds

obj-y	:= setup.o idle.o or32_ksyms.o process.o dma.o \
	   traps.o time.o irq.o entry.o ptrace.o signal.o \
	   sys_call_table.o

obj-$(CONFIG_MODULES)		+= module.o
obj-$(CONFIG_OF)		+= prom.o

clean:
