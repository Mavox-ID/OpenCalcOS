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
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/signal.h>
#include <beep/sched.h>
#include <beep/init.h>
#include <beep/io.h>

#include <asm/thread_notify.h>

#include "soc.h"

struct crunch_state *crunch_owner;

void crunch_task_release(struct thread_info *thread)
{
	local_irq_disable();
	if (crunch_owner == &thread->crunchstate)
		crunch_owner = NULL;
	local_irq_enable();
}

static int crunch_enabled(u32 devcfg)
{
	return !!(devcfg & EP93XX_SYSCON_DEVCFG_CPENA);
}

static int crunch_do(struct notifier_block *self, unsigned long cmd, void *t)
{
	struct thread_info *thread = (struct thread_info *)t;
	struct crunch_state *crunch_state;
	u32 devcfg;

	crunch_state = &thread->crunchstate;

	switch (cmd) {
	case THREAD_NOTIFY_FLUSH:
		memset(crunch_state, 0, sizeof(*crunch_state));

		/*
		 * FALLTHROUGH: Ensure we don't try to overwrite our newly
		 * initialised state information on the first fault.
		 */

	case THREAD_NOTIFY_EXIT:
		crunch_task_release(thread);
		break;

	case THREAD_NOTIFY_SWITCH:
		devcfg = __raw_readl(EP93XX_SYSCON_DEVCFG);
		if (crunch_enabled(devcfg) || crunch_owner == crunch_state) {
			/*
			 * We don't use ep93xx_syscon_swlocked_write() here
			 * because we are on the context switch path and
			 * preemption is already disabled.
			 */
			devcfg ^= EP93XX_SYSCON_DEVCFG_CPENA;
			__raw_writel(0xaa, EP93XX_SYSCON_SWLOCK);
			__raw_writel(devcfg, EP93XX_SYSCON_DEVCFG);
		}
		break;
	}

	return NOTIFY_DONE;
}

static struct notifier_block crunch_notifier_block = {
	.notifier_call	= crunch_do,
};

int __init crunch_init(void)
{
	thread_register_notifier(&crunch_notifier_block);
	elf_hwcap |= HWCAP_CRUNCH;

	return 0;
}
