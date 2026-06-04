	.globl	kernel_start
kernel_start:
	.incbin	"arch/arm/boot/zCalc"
	.globl	kernel_end
kernel_end:
	.align	2
