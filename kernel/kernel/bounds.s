	.arch armv7-a
	.fpu softvfp
	.file	"bounds.c"
@ GNU C17 (GCC) version 14.2.0 (arm-none-eabi)
@	compiled by GNU C version 13.3.0, GMP version 6.3.0, MPFR version 4.2.1, MPC version 1.3.1, isl version none
@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed: -mlittle-endian -mapcs -mno-sched-prolog -mabi=apcs-gnu -mno-thumb-interwork -marm -mfloat-abi=soft -march=armv7-a -g -Os -fno-strict-aliasing -fno-common -fno-delete-null-pointer-checks -fno-dwarf2-cfi-asm -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-overflow -fconserve-stack
	.text
.Ltext0:
	.file 1 "kernel/bounds.c"
	.align	2
	.global	foo
	.syntax unified
	.arm
	.type	foo, %function
foo:
.LFB134:
	.loc 1 26 1 view -0
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp	@,
.LCFI0:
	push	{fp, ip, lr, pc}	@
.LCFI1:
	sub	fp, ip, #4	@,,
.LCFI2:
	.loc 1 28 2 view .LVU1
	.syntax divided
@ 28 "kernel/bounds.c" 1
	
->NR_PAGEFLAGS #22 __NR_PAGEFLAGS	@
@ 0 "" 2
	.loc 1 29 2 view .LVU2
@ 29 "kernel/bounds.c" 1
	
->MAX_NR_ZONES #2 __MAX_NR_ZONES	@
@ 0 "" 2
	.loc 1 30 2 view .LVU3
@ 30 "kernel/bounds.c" 1
	
->NR_PCG_FLAGS #3 __NR_PCG_FLAGS	@
@ 0 "" 2
@ kernel/bounds.c:32: }
	.loc 1 32 1 is_stmt 0 view .LVU4
	.arm
	.syntax unified
	ldmfd	sp, {fp, sp, pc}	@
.LFE134:
	.size	foo, .-foo
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
	.4byte	.LFB134
	.4byte	.LFE134-.LFB134
	.byte	0x4
	.4byte	.LCFI0-.LFB134
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
	.file 2 "include/beep/page-flags.h"
	.file 3 "include/beep/mmzone.h"
	.file 4 "include/beep/page_cgroup.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x191
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x3
	.4byte	.LASF48
	.byte	0x1d
	.4byte	.LASF49
	.4byte	.LASF50
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF10
	.uleb128 0x5
	.4byte	.LASF39
	.byte	0x7
	.byte	0x4
	.4byte	0x49
	.byte	0x2
	.byte	0x57
	.byte	0x6
	.4byte	0x135
	.uleb128 0x1
	.4byte	.LASF11
	.byte	0
	.uleb128 0x1
	.4byte	.LASF12
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF13
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF14
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0xb
	.byte	0
	.uleb128 0x6
	.4byte	.LASF40
	.byte	0x7
	.byte	0x4
	.4byte	0x49
	.byte	0x3
	.2byte	0x102
	.byte	0x6
	.4byte	0x15b
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x2
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.byte	0x4
	.4byte	0x49
	.byte	0x4
	.byte	0x4
	.byte	0x6
	.4byte	0x182
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0x3
	.byte	0
	.uleb128 0x8
	.ascii	"foo\000"
	.byte	0x1
	.byte	0x19
	.byte	0x6
	.4byte	.LFB134
	.4byte	.LFE134-.LFB134
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2
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
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
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
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x4
	.byte	0x1
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
	.uleb128 0x8
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
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
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF46:
	.ascii	"PCG_MIGRATION\000"
.LASF25:
	.ascii	"PG_head\000"
.LASF21:
	.ascii	"PG_reserved\000"
.LASF41:
	.ascii	"ZONE_NORMAL\000"
.LASF28:
	.ascii	"PG_mappedtodisk\000"
.LASF11:
	.ascii	"PG_locked\000"
.LASF15:
	.ascii	"PG_dirty\000"
.LASF24:
	.ascii	"PG_writeback\000"
.LASF22:
	.ascii	"PG_private\000"
.LASF33:
	.ascii	"__NR_PAGEFLAGS\000"
.LASF43:
	.ascii	"__MAX_NR_ZONES\000"
.LASF35:
	.ascii	"PG_fscache\000"
.LASF13:
	.ascii	"PG_referenced\000"
.LASF27:
	.ascii	"PG_swapcache\000"
.LASF40:
	.ascii	"zone_type\000"
.LASF7:
	.ascii	"long unsigned int\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF48:
	.ascii	"GNU C17 14.2.0 -mlittle-endian -mapcs -mno-sched-pr"
	.ascii	"olog -mabi=apcs-gnu -mno-thumb-interwork -marm -mfl"
	.ascii	"oat-abi=soft -march=armv7-a -g -Os -fno-strict-alia"
	.ascii	"sing -fno-common -fno-delete-null-pointer-checks -f"
	.ascii	"no-dwarf2-cfi-asm -fno-stack-protector -fno-omit-fr"
	.ascii	"ame-pointer -fno-optimize-sibling-calls -fno-strict"
	.ascii	"-overflow -fconserve-stack\000"
.LASF34:
	.ascii	"PG_checked\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF49:
	.ascii	"kernel/bounds.c\000"
.LASF26:
	.ascii	"PG_tail\000"
.LASF39:
	.ascii	"pageflags\000"
.LASF44:
	.ascii	"PCG_LOCK\000"
.LASF4:
	.ascii	"unsigned int\000"
.LASF12:
	.ascii	"PG_error\000"
.LASF6:
	.ascii	"long long unsigned int\000"
.LASF36:
	.ascii	"PG_pinned\000"
.LASF18:
	.ascii	"PG_slab\000"
.LASF19:
	.ascii	"PG_owner_priv_1\000"
.LASF17:
	.ascii	"PG_active\000"
.LASF23:
	.ascii	"PG_private_2\000"
.LASF5:
	.ascii	"long long int\000"
.LASF16:
	.ascii	"PG_lru\000"
.LASF8:
	.ascii	"char\000"
.LASF31:
	.ascii	"PG_unevictable\000"
.LASF37:
	.ascii	"PG_savepinned\000"
.LASF2:
	.ascii	"short int\000"
.LASF45:
	.ascii	"PCG_USED\000"
.LASF20:
	.ascii	"PG_arch_1\000"
.LASF9:
	.ascii	"long int\000"
.LASF42:
	.ascii	"ZONE_MOVABLE\000"
.LASF14:
	.ascii	"PG_uptodate\000"
.LASF47:
	.ascii	"__NR_PCG_FLAGS\000"
.LASF0:
	.ascii	"signed char\000"
.LASF29:
	.ascii	"PG_reclaim\000"
.LASF30:
	.ascii	"PG_swapbacked\000"
.LASF10:
	.ascii	"_Bool\000"
.LASF50:
	.ascii	"/home/runner/work/OpenCalcOS/OpenCalcOS/kernel\000"
.LASF32:
	.ascii	"PG_mlocked\000"
.LASF38:
	.ascii	"PG_slob_free\000"
	.ident	"GCC: (GNU) 14.2.0"
