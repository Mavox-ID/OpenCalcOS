/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _ASM_IRQFLAGS_H
#define _ASM_IRQFLAGS_H

#ifndef __ASSEMBLY__
/*
 * Get definitions for arch_local_save_flags(x), etc.
 */
#include <asm/hw_irq.h>

#else
#ifdef CONFIG_TRACE_IRQFLAGS
#ifdef CONFIG_IRQSOFF_TRACER
/*
 * Since the ftrace irqsoff latency trace checks CALLER_ADDR1,
 * which is the stack frame here, we need to force a stack frame
 * in case we came from user space.
 */
#define TRACE_WITH_FRAME_BUFFER(func)		\
	mflr	r0;				\
	stdu	r1, -32(r1);			\
	std	r0, 16(r1);			\
	stdu	r1, -32(r1);			\
	bl func;				\
	ld	r1, 0(r1);			\
	ld	r1, 0(r1);
#else
#define TRACE_WITH_FRAME_BUFFER(func)		\
	bl func;
#endif

/*
 * Most of the CPU's IRQ-state tracing is done from assembly code; we
 * have to call a C function so call a wrapper that saves all the
 * C-clobbered registers.
 */
#define TRACE_ENABLE_INTS	TRACE_WITH_FRAME_BUFFER(.trace_hardirqs_on)
#define TRACE_DISABLE_INTS	TRACE_WITH_FRAME_BUFFER(.trace_hardirqs_off)

/*
 * This is used by assembly code to soft-disable interrupts
 */
#define SOFT_DISABLE_INTS(__rA, __rB)		\
	lbz	__rA,PACASOFTIRQEN(r13);	\
	lbz	__rB,PACAIRQHAPPENED(r13);	\
	cmpwi	cr0,__rA,0;			\
	li	__rA,0;				\
	ori	__rB,__rB,PACA_IRQ_HARD_DIS;	\
	stb	__rB,PACAIRQHAPPENED(r13);	\
	beq	44f;				\
	stb	__rA,PACASOFTIRQEN(r13);	\
	TRACE_DISABLE_INTS;			\
44:

#else
#define TRACE_ENABLE_INTS
#define TRACE_DISABLE_INTS

#define SOFT_DISABLE_INTS(__rA, __rB)		\
	lbz	__rA,PACAIRQHAPPENED(r13);	\
	li	__rB,0;				\
	ori	__rA,__rA,PACA_IRQ_HARD_DIS;	\
	stb	__rB,PACASOFTIRQEN(r13);	\
	stb	__rA,PACAIRQHAPPENED(r13)
#endif
#endif

#endif
