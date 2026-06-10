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
#include <asm/irqflags.h>
#include <asm/hazards.h>
#include <beep/compiler.h>
#include <beep/preempt.h>
#include <beep/export.h>

#if !defined(CONFIG_CPU_MIPSR2) || defined(CONFIG_MIPS_MT_SMTC)

/*
 * For cli() we have to insert nops to make sure that the new value
 * has actually arrived in the status register before the end of this
 * macro.
 * R4000/R4400 need three nops, the R4600 two nops and the R10000 needs
 * no nops at all.
 */
/*
 * For TX49, operating only IE bit is not enough.
 *
 * If mfc0 $12 follows store and the mfc0 is last instruction of a
 * page and fetching the next instruction causes TLB miss, the result
 * of the mfc0 might wrongly contain EXL bit.
 *
 * ERT-TX49H2-027, ERT-TX49H3-012, ERT-TX49HL3-006, ERT-TX49H4-008
 *
 * Workaround: mask EXL bit of the result or place a nop before mfc0.
 */
__asm__(
	"	.macro	arch_local_irq_disable\n"
	"	.set	push						\n"
	"	.set	noat						\n"
#ifdef CONFIG_MIPS_MT_SMTC
	"	mfc0	$1, $2, 1					\n"
	"	ori	$1, 0x400					\n"
	"	.set	noreorder					\n"
	"	mtc0	$1, $2, 1					\n"
#elif defined(CONFIG_CPU_MIPSR2)
	/* see irqflags.h for inline function */
#else
	"	mfc0	$1,$12						\n"
	"	ori	$1,0x1f						\n"
	"	xori	$1,0x1f						\n"
	"	.set	noreorder					\n"
	"	mtc0	$1,$12						\n"
#endif
	"	irq_disable_hazard					\n"
	"	.set	pop						\n"
	"	.endm							\n");

notrace void arch_local_irq_disable(void)
{
	preempt_disable();
	__asm__ __volatile__(
		"arch_local_irq_disable"
		: /* no outputs */
		: /* no inputs */
		: "memory");
	preempt_enable();
}
EXPORT_SYMBOL(arch_local_irq_disable);


__asm__(
	"	.macro	arch_local_irq_save result			\n"
	"	.set	push						\n"
	"	.set	reorder						\n"
	"	.set	noat						\n"
#ifdef CONFIG_MIPS_MT_SMTC
	"	mfc0	\\result, $2, 1					\n"
	"	ori	$1, \\result, 0x400				\n"
	"	.set	noreorder					\n"
	"	mtc0	$1, $2, 1					\n"
	"	andi	\\result, \\result, 0x400			\n"
#elif defined(CONFIG_CPU_MIPSR2)
	/* see irqflags.h for inline function */
#else
	"	mfc0	\\result, $12					\n"
	"	ori	$1, \\result, 0x1f				\n"
	"	xori	$1, 0x1f					\n"
	"	.set	noreorder					\n"
	"	mtc0	$1, $12						\n"
#endif
	"	irq_disable_hazard					\n"
	"	.set	pop						\n"
	"	.endm							\n");

notrace unsigned long arch_local_irq_save(void)
{
	unsigned long flags;
	preempt_disable();
	asm volatile("arch_local_irq_save\t%0"
		     : "=r" (flags)
		     : /* no inputs */
		     : "memory");
	preempt_enable();
	return flags;
}
EXPORT_SYMBOL(arch_local_irq_save);


__asm__(
	"	.macro	arch_local_irq_restore flags			\n"
	"	.set	push						\n"
	"	.set	noreorder					\n"
	"	.set	noat						\n"
#ifdef CONFIG_MIPS_MT_SMTC
	"mfc0	$1, $2, 1						\n"
	"andi	\\flags, 0x400						\n"
	"ori	$1, 0x400						\n"
	"xori	$1, 0x400						\n"
	"or	\\flags, $1						\n"
	"mtc0	\\flags, $2, 1						\n"
#elif defined(CONFIG_CPU_MIPSR2) && defined(CONFIG_IRQ_CPU)
	/* see irqflags.h for inline function */
#elif defined(CONFIG_CPU_MIPSR2)
	/* see irqflags.h for inline function */
#else
	"	mfc0	$1, $12						\n"
	"	andi	\\flags, 1					\n"
	"	ori	$1, 0x1f					\n"
	"	xori	$1, 0x1f					\n"
	"	or	\\flags, $1					\n"
	"	mtc0	\\flags, $12					\n"
#endif
	"	irq_disable_hazard					\n"
	"	.set	pop						\n"
	"	.endm							\n");

notrace void arch_local_irq_restore(unsigned long flags)
{
	unsigned long __tmp1;

#ifdef CONFIG_MIPS_MT_SMTC
	/*
	 * SMTC kernel needs to do a software replay of queued
	 * IPIs, at the cost of branch and call overhead on each
	 * local_irq_restore()
	 */
	if (unlikely(!(flags & 0x0400)))
		smtc_ipi_replay();
#endif
	preempt_disable();
	__asm__ __volatile__(
		"arch_local_irq_restore\t%0"
		: "=r" (__tmp1)
		: "0" (flags)
		: "memory");
	preempt_enable();
}
EXPORT_SYMBOL(arch_local_irq_restore);


notrace void __arch_local_irq_restore(unsigned long flags)
{
	unsigned long __tmp1;

	preempt_disable();
	__asm__ __volatile__(
		"arch_local_irq_restore\t%0"
		: "=r" (__tmp1)
		: "0" (flags)
		: "memory");
	preempt_enable();
}
EXPORT_SYMBOL(__arch_local_irq_restore);

#endif /* !defined(CONFIG_CPU_MIPSR2) || defined(CONFIG_MIPS_MT_SMTC) */
