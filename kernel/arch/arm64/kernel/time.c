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
#include <beep/export.h>
#include <beep/kernel.h>
#include <beep/interrupt.h>
#include <beep/time.h>
#include <beep/init.h>
#include <beep/sched.h>
#include <beep/smp.h>
#include <beep/timex.h>
#include <beep/errno.h>
#include <beep/profile.h>
#include <beep/syscore_ops.h>
#include <beep/timer.h>
#include <beep/irq.h>

#include <clocksource/arm_generic.h>

#include <asm/thread_info.h>
#include <asm/stacktrace.h>

#ifdef CONFIG_SMP
unsigned long profile_pc(struct pt_regs *regs)
{
	struct stackframe frame;

	if (!in_lock_functions(regs->pc))
		return regs->pc;

	frame.fp = regs->regs[29];
	frame.sp = regs->sp;
	frame.pc = regs->pc;
	do {
		int ret = unwind_frame(&frame);
		if (ret < 0)
			return 0;
	} while (in_lock_functions(frame.pc));

	return frame.pc;
}
EXPORT_SYMBOL(profile_pc);
#endif

void __init time_init(void)
{
	arm_generic_timer_init();
}
