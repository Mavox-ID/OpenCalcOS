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
#include <beep/module.h>
#include <beep/sched.h>
#include <beep/pm.h>
#include <beep/tick.h>
#include <beep/bitops.h>
#include <beep/ptrace.h>
#include <asm/pgalloc.h>
#include <asm/uaccess.h> /* for USER_DS macros */
#include <asm/cacheflush.h>

void show_regs(struct pt_regs *regs)
{
	printk(KERN_INFO " Registers dump: mode=%X\r\n", regs->pt_mode);
	printk(KERN_INFO " r1=%08lX, r2=%08lX, r3=%08lX, r4=%08lX\n",
				regs->r1, regs->r2, regs->r3, regs->r4);
	printk(KERN_INFO " r5=%08lX, r6=%08lX, r7=%08lX, r8=%08lX\n",
				regs->r5, regs->r6, regs->r7, regs->r8);
	printk(KERN_INFO " r9=%08lX, r10=%08lX, r11=%08lX, r12=%08lX\n",
				regs->r9, regs->r10, regs->r11, regs->r12);
	printk(KERN_INFO " r13=%08lX, r14=%08lX, r15=%08lX, r16=%08lX\n",
				regs->r13, regs->r14, regs->r15, regs->r16);
	printk(KERN_INFO " r17=%08lX, r18=%08lX, r19=%08lX, r20=%08lX\n",
				regs->r17, regs->r18, regs->r19, regs->r20);
	printk(KERN_INFO " r21=%08lX, r22=%08lX, r23=%08lX, r24=%08lX\n",
				regs->r21, regs->r22, regs->r23, regs->r24);
	printk(KERN_INFO " r25=%08lX, r26=%08lX, r27=%08lX, r28=%08lX\n",
				regs->r25, regs->r26, regs->r27, regs->r28);
	printk(KERN_INFO " r29=%08lX, r30=%08lX, r31=%08lX, rPC=%08lX\n",
				regs->r29, regs->r30, regs->r31, regs->pc);
	printk(KERN_INFO " msr=%08lX, ear=%08lX, esr=%08lX, fsr=%08lX\n",
				regs->msr, regs->ear, regs->esr, regs->fsr);
}

void (*pm_idle)(void);
void (*pm_power_off)(void) = NULL;
EXPORT_SYMBOL(pm_power_off);

static int hlt_counter = 1;

void disable_hlt(void)
{
	hlt_counter++;
}
EXPORT_SYMBOL(disable_hlt);

void enable_hlt(void)
{
	hlt_counter--;
}
EXPORT_SYMBOL(enable_hlt);

static int __init nohlt_setup(char *__unused)
{
	hlt_counter = 1;
	return 1;
}
__setup("nohlt", nohlt_setup);

static int __init hlt_setup(char *__unused)
{
	hlt_counter = 0;
	return 1;
}
__setup("hlt", hlt_setup);

void default_idle(void)
{
	if (likely(hlt_counter)) {
		local_irq_disable();
		stop_critical_timings();
		cpu_relax();
		start_critical_timings();
		local_irq_enable();
	} else {
		clear_thread_flag(TIF_POLLING_NRFLAG);
		smp_mb__after_clear_bit();
		local_irq_disable();
		while (!need_resched())
			cpu_sleep();
		local_irq_enable();
		set_thread_flag(TIF_POLLING_NRFLAG);
	}
}

void cpu_idle(void)
{
	set_thread_flag(TIF_POLLING_NRFLAG);

	/* endless idle loop with no priority at all */
	while (1) {
		void (*idle)(void) = pm_idle;

		if (!idle)
			idle = default_idle;

		tick_nohz_idle_enter();
		rcu_idle_enter();
		while (!need_resched())
			idle();
		rcu_idle_exit();
		tick_nohz_idle_exit();

		schedule_preempt_disabled();
		check_pgt_cache();
	}
}

void flush_thread(void)
{
}

int copy_thread(unsigned long clone_flags, unsigned long usp,
		unsigned long arg, struct task_struct *p)
{
	struct pt_regs *childregs = task_pt_regs(p);
	struct thread_info *ti = task_thread_info(p);

	if (unlikely(p->flags & PF_KTHREAD)) {
		/* if we're creating a new kernel thread then just zeroing all
		 * the registers. That's OK for a brand new thread.*/
		memset(childregs, 0, sizeof(struct pt_regs));
		memset(&ti->cpu_context, 0, sizeof(struct cpu_context));
		ti->cpu_context.r1  = (unsigned long)childregs;
		ti->cpu_context.r20 = (unsigned long)usp; /* fn */
		ti->cpu_context.r19 = (unsigned long)arg;
		childregs->pt_mode = 1;
		local_save_flags(childregs->msr);
#ifdef CONFIG_MMU
		ti->cpu_context.msr = childregs->msr & ~MSR_IE;
#endif
		ti->cpu_context.r15 = (unsigned long)ret_from_kernel_thread - 8;
		return 0;
	}
	*childregs = *current_pt_regs();
	if (usp)
		childregs->r1 = usp;

	memset(&ti->cpu_context, 0, sizeof(struct cpu_context));
	ti->cpu_context.r1 = (unsigned long)childregs;
#ifndef CONFIG_MMU
	ti->cpu_context.msr = (unsigned long)childregs->msr;
#else
	childregs->msr |= MSR_UMS;

	/* we should consider the fact that childregs is a copy of the parent
	 * regs which were saved immediately after entering the kernel state
	 * before enabling VM. This MSR will be restored in switch_to and
	 * RETURN() and we want to have the right machine state there
	 * specifically this state must have INTs disabled before and enabled
	 * after performing rtbd
	 * compose the right MSR for RETURN(). It will work for switch_to also
	 * excepting for VM and UMS
	 * don't touch UMS , CARRY and cache bits
	 * right now MSR is a copy of parent one */
	childregs->msr &= ~MSR_EIP;
	childregs->msr |= MSR_IE;
	childregs->msr &= ~MSR_VM;
	childregs->msr |= MSR_VMS;
	childregs->msr |= MSR_EE; /* exceptions will be enabled*/

	ti->cpu_context.msr = (childregs->msr|MSR_VM);
	ti->cpu_context.msr &= ~MSR_UMS; /* switch_to to kernel mode */
	ti->cpu_context.msr &= ~MSR_IE;
#endif
	ti->cpu_context.r15 = (unsigned long)ret_from_fork - 8;

	/*
	 *  r21 is the thread reg, r10 is 6th arg to clone
	 *  which contains TLS area
	 */
	if (clone_flags & CLONE_SETTLS)
		childregs->r21 = childregs->r10;

	return 0;
}

#ifndef CONFIG_MMU
/*
 * Return saved PC of a blocked thread.
 */
unsigned long thread_saved_pc(struct task_struct *tsk)
{
	struct cpu_context *ctx =
		&(((struct thread_info *)(tsk->stack))->cpu_context);

	/* Check whether the thread is blocked in resume() */
	if (in_sched_functions(ctx->r15))
		return (unsigned long)ctx->r15;
	else
		return ctx->r14;
}
#endif

unsigned long get_wchan(struct task_struct *p)
{
/* TBD (used by procfs) */
	return 0;
}

/* Set up a thread for executing a new program */
void start_thread(struct pt_regs *regs, unsigned long pc, unsigned long usp)
{
	regs->pc = pc;
	regs->r1 = usp;
	regs->pt_mode = 0;
#ifdef CONFIG_MMU
	regs->msr |= MSR_UMS;
	regs->msr &= ~MSR_VM;
#endif
}

#ifdef CONFIG_MMU
#include <beep/elfcore.h>
/*
 * Set up a thread for executing a new program
 */
int dump_fpu(struct pt_regs *regs, elf_fpregset_t *fpregs)
{
	return 0; /* MicroBlaze has no separate FPU registers */
}
#endif /* CONFIG_MMU */
