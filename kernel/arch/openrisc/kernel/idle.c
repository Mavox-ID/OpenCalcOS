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
#include <beep/errno.h>
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/mm.h>
#include <beep/smp.h>
#include <beep/stddef.h>
#include <beep/unistd.h>
#include <beep/ptrace.h>
#include <beep/slab.h>
#include <beep/tick.h>

#include <asm/pgtable.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/processor.h>
#include <asm/mmu.h>
#include <asm/cache.h>
#include <asm/pgalloc.h>

void (*powersave) (void) = NULL;

static inline void pm_idle(void)
{
	barrier();
}

void cpu_idle(void)
{
	set_thread_flag(TIF_POLLING_NRFLAG);

	/* endless idle loop with no priority at all */
	while (1) {
		tick_nohz_idle_enter();
		rcu_idle_enter();

		while (!need_resched()) {
			check_pgt_cache();
			rmb();

			clear_thread_flag(TIF_POLLING_NRFLAG);

			local_irq_disable();
			/* Don't trace irqs off for idle */
			stop_critical_timings();
			if (!need_resched() && powersave != NULL)
				powersave();
			start_critical_timings();
			local_irq_enable();
			set_thread_flag(TIF_POLLING_NRFLAG);
		}

		rcu_idle_exit();
		tick_nohz_idle_exit();
		preempt_enable_no_resched();
		schedule();
		preempt_disable();
	}
}
