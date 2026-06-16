	.arch armv7-a
	.fpu softvfp
	.file	"asm-offsets.c"
@ GNU C17 (GCC) version 14.2.0 (arm-none-eabi)
@	compiled by GNU C version 13.3.0, GMP version 6.3.0, MPFR version 4.2.1, MPC version 1.3.1, isl version none
@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed: -mlittle-endian -mapcs -mno-sched-prolog -mabi=apcs-gnu -mno-thumb-interwork -marm -mfloat-abi=soft -march=armv7-a -g -Os -fno-strict-aliasing -fno-common -fno-delete-null-pointer-checks -fno-dwarf2-cfi-asm -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-overflow -fconserve-stack
	.text
.Ltext0:
	.file 1 "arch/arm/kernel/asm-offsets.c"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
.LFB1250:
	.loc 1 50 1 view -0
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp	@,
.LCFI0:
	push	{fp, ip, lr, pc}	@
.LCFI1:
	sub	fp, ip, #4	@,,
.LCFI2:
	.loc 1 51 3 view .LVU1
	.syntax divided
@ 51 "arch/arm/kernel/asm-offsets.c" 1
	
->TSK_ACTIVE_MM #164 offsetof(struct task_struct, active_mm)	@
@ 0 "" 2
	.loc 1 55 3 view .LVU2
@ 55 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 56 3 view .LVU3
@ 56 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_FLAGS #0 offsetof(struct thread_info, flags)	@
@ 0 "" 2
	.loc 1 57 3 view .LVU4
@ 57 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_PREEMPT #4 offsetof(struct thread_info, preempt_count)	@
@ 0 "" 2
	.loc 1 58 3 view .LVU5
@ 58 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_ADDR_LIMIT #8 offsetof(struct thread_info, addr_limit)	@
@ 0 "" 2
	.loc 1 59 3 view .LVU6
@ 59 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_TASK #12 offsetof(struct thread_info, task)	@
@ 0 "" 2
	.loc 1 60 3 view .LVU7
@ 60 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_EXEC_DOMAIN #16 offsetof(struct thread_info, exec_domain)	@
@ 0 "" 2
	.loc 1 61 3 view .LVU8
@ 61 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_CPU #20 offsetof(struct thread_info, cpu)	@
@ 0 "" 2
	.loc 1 62 3 view .LVU9
@ 62 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_CPU_DOMAIN #24 offsetof(struct thread_info, cpu_domain)	@
@ 0 "" 2
	.loc 1 63 3 view .LVU10
@ 63 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_CPU_SAVE #28 offsetof(struct thread_info, cpu_context)	@
@ 0 "" 2
	.loc 1 64 3 view .LVU11
@ 64 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_USED_CP #80 offsetof(struct thread_info, used_cp)	@
@ 0 "" 2
	.loc 1 65 3 view .LVU12
@ 65 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_TP_VALUE #96 offsetof(struct thread_info, tp_value)	@
@ 0 "" 2
	.loc 1 66 3 view .LVU13
@ 66 "arch/arm/kernel/asm-offsets.c" 1
	
->TI_FPSTATE #104 offsetof(struct thread_info, fpstate)	@
@ 0 "" 2
	.loc 1 82 3 view .LVU14
@ 82 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 83 3 view .LVU15
@ 83 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R0 #0 offsetof(struct pt_regs, ARM_r0)	@
@ 0 "" 2
	.loc 1 84 3 view .LVU16
@ 84 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R1 #4 offsetof(struct pt_regs, ARM_r1)	@
@ 0 "" 2
	.loc 1 85 3 view .LVU17
@ 85 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R2 #8 offsetof(struct pt_regs, ARM_r2)	@
@ 0 "" 2
	.loc 1 86 3 view .LVU18
@ 86 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R3 #12 offsetof(struct pt_regs, ARM_r3)	@
@ 0 "" 2
	.loc 1 87 3 view .LVU19
@ 87 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R4 #16 offsetof(struct pt_regs, ARM_r4)	@
@ 0 "" 2
	.loc 1 88 3 view .LVU20
@ 88 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R5 #20 offsetof(struct pt_regs, ARM_r5)	@
@ 0 "" 2
	.loc 1 89 3 view .LVU21
@ 89 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R6 #24 offsetof(struct pt_regs, ARM_r6)	@
@ 0 "" 2
	.loc 1 90 3 view .LVU22
@ 90 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R7 #28 offsetof(struct pt_regs, ARM_r7)	@
@ 0 "" 2
	.loc 1 91 3 view .LVU23
@ 91 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R8 #32 offsetof(struct pt_regs, ARM_r8)	@
@ 0 "" 2
	.loc 1 92 3 view .LVU24
@ 92 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R9 #36 offsetof(struct pt_regs, ARM_r9)	@
@ 0 "" 2
	.loc 1 93 3 view .LVU25
@ 93 "arch/arm/kernel/asm-offsets.c" 1
	
->S_R10 #40 offsetof(struct pt_regs, ARM_r10)	@
@ 0 "" 2
	.loc 1 94 3 view .LVU26
@ 94 "arch/arm/kernel/asm-offsets.c" 1
	
->S_FP #44 offsetof(struct pt_regs, ARM_fp)	@
@ 0 "" 2
	.loc 1 95 3 view .LVU27
@ 95 "arch/arm/kernel/asm-offsets.c" 1
	
->S_IP #48 offsetof(struct pt_regs, ARM_ip)	@
@ 0 "" 2
	.loc 1 96 3 view .LVU28
@ 96 "arch/arm/kernel/asm-offsets.c" 1
	
->S_SP #52 offsetof(struct pt_regs, ARM_sp)	@
@ 0 "" 2
	.loc 1 97 3 view .LVU29
@ 97 "arch/arm/kernel/asm-offsets.c" 1
	
->S_LR #56 offsetof(struct pt_regs, ARM_lr)	@
@ 0 "" 2
	.loc 1 98 3 view .LVU30
@ 98 "arch/arm/kernel/asm-offsets.c" 1
	
->S_PC #60 offsetof(struct pt_regs, ARM_pc)	@
@ 0 "" 2
	.loc 1 99 3 view .LVU31
@ 99 "arch/arm/kernel/asm-offsets.c" 1
	
->S_PSR #64 offsetof(struct pt_regs, ARM_cpsr)	@
@ 0 "" 2
	.loc 1 100 3 view .LVU32
@ 100 "arch/arm/kernel/asm-offsets.c" 1
	
->S_OLD_R0 #68 offsetof(struct pt_regs, ARM_ORIG_r0)	@
@ 0 "" 2
	.loc 1 101 3 view .LVU33
@ 101 "arch/arm/kernel/asm-offsets.c" 1
	
->S_FRAME_SIZE #72 sizeof(struct pt_regs)	@
@ 0 "" 2
	.loc 1 102 3 view .LVU34
@ 102 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 104 3 view .LVU35
@ 104 "arch/arm/kernel/asm-offsets.c" 1
	
->L2X0_R_PHY_BASE #0 offsetof(struct l2x0_regs, phy_base)	@
@ 0 "" 2
	.loc 1 105 3 view .LVU36
@ 105 "arch/arm/kernel/asm-offsets.c" 1
	
->L2X0_R_AUX_CTRL #4 offsetof(struct l2x0_regs, aux_ctrl)	@
@ 0 "" 2
	.loc 1 106 3 view .LVU37
@ 106 "arch/arm/kernel/asm-offsets.c" 1
	
->L2X0_R_TAG_LATENCY #8 offsetof(struct l2x0_regs, tag_latency)	@
@ 0 "" 2
	.loc 1 107 3 view .LVU38
@ 107 "arch/arm/kernel/asm-offsets.c" 1
	
->L2X0_R_DATA_LATENCY #12 offsetof(struct l2x0_regs, data_latency)	@
@ 0 "" 2
	.loc 1 108 3 view .LVU39
@ 108 "arch/arm/kernel/asm-offsets.c" 1
	
->L2X0_R_FILTER_START #16 offsetof(struct l2x0_regs, filter_start)	@
@ 0 "" 2
	.loc 1 109 3 view .LVU40
@ 109 "arch/arm/kernel/asm-offsets.c" 1
	
->L2X0_R_FILTER_END #20 offsetof(struct l2x0_regs, filter_end)	@
@ 0 "" 2
	.loc 1 110 3 view .LVU41
@ 110 "arch/arm/kernel/asm-offsets.c" 1
	
->L2X0_R_PREFETCH_CTRL #24 offsetof(struct l2x0_regs, prefetch_ctrl)	@
@ 0 "" 2
	.loc 1 111 3 view .LVU42
@ 111 "arch/arm/kernel/asm-offsets.c" 1
	
->L2X0_R_PWR_CTRL #28 offsetof(struct l2x0_regs, pwr_ctrl)	@
@ 0 "" 2
	.loc 1 112 3 view .LVU43
@ 112 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 115 3 view .LVU44
@ 115 "arch/arm/kernel/asm-offsets.c" 1
	
->MM_CONTEXT_ID #340 offsetof(struct mm_struct, context.id)	@
@ 0 "" 2
	.loc 1 116 3 view .LVU45
@ 116 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 118 3 view .LVU46
@ 118 "arch/arm/kernel/asm-offsets.c" 1
	
->VMA_VM_MM #32 offsetof(struct vm_area_struct, vm_mm)	@
@ 0 "" 2
	.loc 1 119 3 view .LVU47
@ 119 "arch/arm/kernel/asm-offsets.c" 1
	
->VMA_VM_FLAGS #40 offsetof(struct vm_area_struct, vm_flags)	@
@ 0 "" 2
	.loc 1 120 3 view .LVU48
@ 120 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 121 3 view .LVU49
@ 121 "arch/arm/kernel/asm-offsets.c" 1
	
->VM_EXEC #4 VM_EXEC	@
@ 0 "" 2
	.loc 1 122 3 view .LVU50
@ 122 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 123 3 view .LVU51
@ 123 "arch/arm/kernel/asm-offsets.c" 1
	
->PAGE_SZ #4096 PAGE_SIZE	@
@ 0 "" 2
	.loc 1 124 3 view .LVU52
@ 124 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 125 3 view .LVU53
@ 125 "arch/arm/kernel/asm-offsets.c" 1
	
->SYS_ERROR0 #10420224 0x9f0000	@
@ 0 "" 2
	.loc 1 126 3 view .LVU54
@ 126 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 127 3 view .LVU55
@ 127 "arch/arm/kernel/asm-offsets.c" 1
	
->SIZEOF_MACHINE_DESC #76 sizeof(struct machine_desc)	@
@ 0 "" 2
	.loc 1 128 3 view .LVU56
@ 128 "arch/arm/kernel/asm-offsets.c" 1
	
->MACHINFO_TYPE #0 offsetof(struct machine_desc, nr)	@
@ 0 "" 2
	.loc 1 129 3 view .LVU57
@ 129 "arch/arm/kernel/asm-offsets.c" 1
	
->MACHINFO_NAME #4 offsetof(struct machine_desc, name)	@
@ 0 "" 2
	.loc 1 130 3 view .LVU58
@ 130 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 131 3 view .LVU59
@ 131 "arch/arm/kernel/asm-offsets.c" 1
	
->PROC_INFO_SZ #52 sizeof(struct proc_info_list)	@
@ 0 "" 2
	.loc 1 132 3 view .LVU60
@ 132 "arch/arm/kernel/asm-offsets.c" 1
	
->PROCINFO_INITFUNC #16 offsetof(struct proc_info_list, __cpu_flush)	@
@ 0 "" 2
	.loc 1 133 3 view .LVU61
@ 133 "arch/arm/kernel/asm-offsets.c" 1
	
->PROCINFO_MM_MMUFLAGS #8 offsetof(struct proc_info_list, __cpu_mm_mmu_flags)	@
@ 0 "" 2
	.loc 1 134 3 view .LVU62
@ 134 "arch/arm/kernel/asm-offsets.c" 1
	
->PROCINFO_IO_MMUFLAGS #12 offsetof(struct proc_info_list, __cpu_io_mmu_flags)	@
@ 0 "" 2
	.loc 1 135 3 view .LVU63
@ 135 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 150 3 view .LVU64
@ 150 "arch/arm/kernel/asm-offsets.c" 1
	
->	
@ 0 "" 2
	.loc 1 151 3 view .LVU65
@ 151 "arch/arm/kernel/asm-offsets.c" 1
	
->DMA_BIDIRECTIONAL #0 DMA_BIDIRECTIONAL	@
@ 0 "" 2
	.loc 1 152 3 view .LVU66
@ 152 "arch/arm/kernel/asm-offsets.c" 1
	
->DMA_TO_DEVICE #1 DMA_TO_DEVICE	@
@ 0 "" 2
	.loc 1 153 3 view .LVU67
@ 153 "arch/arm/kernel/asm-offsets.c" 1
	
->DMA_FROM_DEVICE #2 DMA_FROM_DEVICE	@
@ 0 "" 2
	.loc 1 154 3 view .LVU68
@ arch/arm/kernel/asm-offsets.c:155: }
	.loc 1 155 1 is_stmt 0 view .LVU69
	.arm
	.syntax unified
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.LFE1250:
	.size	main, .-main
	.section	.debug_frame,"",%progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x3
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 -4
	.uleb128 0xe
	.byte	0xc
	.uleb128 0xd
	.uleb128 0
	.align	2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB1250
	.4byte	.LFE1250-.LFB1250
	.byte	0x4
	.4byte	.LCFI0-.LFB1250
	.byte	0xd
	.uleb128 0xc
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0x8b
	.uleb128 0x4
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8e
	.uleb128 0x2
	.byte	0x4
	.4byte	.LCFI2-.LCFI1
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE0:
	.text
.Letext0:
	.file 2 "include/beep/dma-direction.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xb8
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x3
	.4byte	.LASF15
	.byte	0x1d
	.4byte	.LASF16
	.4byte	.LASF17
	.4byte	.LLRL0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x1
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x1
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x1
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x1
	.byte	0x8
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x1
	.byte	0x8
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.4byte	.LASF8
	.uleb128 0x1
	.byte	0x4
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x1
	.byte	0x1
	.byte	0x2
	.4byte	.LASF10
	.uleb128 0x5
	.4byte	.LASF18
	.byte	0x7
	.byte	0x4
	.4byte	0x49
	.byte	0x2
	.byte	0x7
	.byte	0x6
	.4byte	0xa5
	.uleb128 0x2
	.4byte	.LASF11
	.byte	0
	.uleb128 0x2
	.4byte	.LASF12
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF13
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF14
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.4byte	.LASF19
	.byte	0x1
	.byte	0x31
	.byte	0x5
	.4byte	0x26
	.4byte	.LFB1250
	.4byte	.LFE1250-.LFB1250
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB1250
	.4byte	.LFE1250-.LFB1250
	.4byte	0
	.4byte	0
	.section	.debug_rnglists,"",%progbits
.Ldebug_ranges0:
	.4byte	.Ldebug_ranges3-.Ldebug_ranges2
.Ldebug_ranges2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.LLRL0:
	.byte	0x7
	.4byte	.LFB1250
	.uleb128 .LFE1250-.LFB1250
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF18:
	.ascii	"dma_data_direction\000"
.LASF14:
	.ascii	"DMA_NONE\000"
.LASF16:
	.ascii	"arch/arm/kernel/asm-offsets.c\000"
.LASF19:
	.ascii	"main\000"
.LASF13:
	.ascii	"DMA_FROM_DEVICE\000"
.LASF11:
	.ascii	"DMA_BIDIRECTIONAL\000"
.LASF7:
	.ascii	"long unsigned int\000"
.LASF5:
	.ascii	"long long int\000"
.LASF6:
	.ascii	"long long unsigned int\000"
.LASF12:
	.ascii	"DMA_TO_DEVICE\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF8:
	.ascii	"char\000"
.LASF9:
	.ascii	"long int\000"
.LASF10:
	.ascii	"_Bool\000"
.LASF17:
	.ascii	"/home/runner/work/OpenCalcOS/OpenCalcOS/kernel\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF0:
	.ascii	"signed char\000"
.LASF2:
	.ascii	"short int\000"
.LASF4:
	.ascii	"unsigned int\000"
.LASF15:
	.ascii	"GNU C17 14.2.0 -mlittle-endian -mapcs -mno-sched-pr"
	.ascii	"olog -mabi=apcs-gnu -mno-thumb-interwork -marm -mfl"
	.ascii	"oat-abi=soft -march=armv7-a -g -Os -fno-strict-alia"
	.ascii	"sing -fno-common -fno-delete-null-pointer-checks -f"
	.ascii	"no-dwarf2-cfi-asm -fno-stack-protector -fno-omit-fr"
	.ascii	"ame-pointer -fno-optimize-sibling-calls -fno-strict"
	.ascii	"-overflow -fconserve-stack\000"
	.ident	"GCC: (GNU) 14.2.0"
