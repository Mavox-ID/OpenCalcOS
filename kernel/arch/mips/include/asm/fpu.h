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
#ifndef _ASM_FPU_H
#define _ASM_FPU_H

#include <beep/sched.h>
#include <beep/thread_info.h>
#include <beep/bitops.h>

#include <asm/mipsregs.h>
#include <asm/cpu.h>
#include <asm/cpu-features.h>
#include <asm/hazards.h>
#include <asm/processor.h>
#include <asm/current.h>

#ifdef CONFIG_MIPS_MT_FPAFF
#include <asm/mips_mt.h>
#endif

struct sigcontext;
struct sigcontext32;

extern void fpu_emulator_init_fpu(void);
extern void _init_fpu(void);
extern void _save_fp(struct task_struct *);
extern void _restore_fp(struct task_struct *);

#define __enable_fpu()							\
do {									\
        set_c0_status(ST0_CU1);						\
        enable_fpu_hazard();						\
} while (0)

#define __disable_fpu()							\
do {									\
	clear_c0_status(ST0_CU1);					\
        disable_fpu_hazard();						\
} while (0)

#define enable_fpu()							\
do {									\
	if (cpu_has_fpu)						\
		__enable_fpu();						\
} while (0)

#define disable_fpu()							\
do {									\
	if (cpu_has_fpu)						\
		__disable_fpu();					\
} while (0)


#define clear_fpu_owner()	clear_thread_flag(TIF_USEDFPU)

static inline int __is_fpu_owner(void)
{
	return test_thread_flag(TIF_USEDFPU);
}

static inline int is_fpu_owner(void)
{
	return cpu_has_fpu && __is_fpu_owner();
}

static inline void __own_fpu(void)
{
	__enable_fpu();
	KSTK_STATUS(current) |= ST0_CU1;
	set_thread_flag(TIF_USEDFPU);
}

static inline void own_fpu_inatomic(int restore)
{
	if (cpu_has_fpu && !__is_fpu_owner()) {
		__own_fpu();
		if (restore)
			_restore_fp(current);
	}
}

static inline void own_fpu(int restore)
{
	preempt_disable();
	own_fpu_inatomic(restore);
	preempt_enable();
}

static inline void lose_fpu(int save)
{
	preempt_disable();
	if (is_fpu_owner()) {
		if (save)
			_save_fp(current);
		KSTK_STATUS(current) &= ~ST0_CU1;
		clear_thread_flag(TIF_USEDFPU);
		__disable_fpu();
	}
	preempt_enable();
}

static inline void init_fpu(void)
{
	preempt_disable();
	if (cpu_has_fpu) {
		__own_fpu();
		_init_fpu();
	} else {
		fpu_emulator_init_fpu();
	}
	preempt_enable();
}

static inline void save_fp(struct task_struct *tsk)
{
	if (cpu_has_fpu)
		_save_fp(tsk);
}

static inline void restore_fp(struct task_struct *tsk)
{
	if (cpu_has_fpu)
		_restore_fp(tsk);
}

static inline fpureg_t *get_fpu_regs(struct task_struct *tsk)
{
	if (tsk == current) {
		preempt_disable();
		if (is_fpu_owner())
			_save_fp(current);
		preempt_enable();
	}

	return tsk->thread.fpu.fpr;
}

#endif /* _ASM_FPU_H */
