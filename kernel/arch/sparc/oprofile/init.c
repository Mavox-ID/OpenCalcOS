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
#include <beep/kernel.h>
#include <beep/oprofile.h>
#include <beep/errno.h>
#include <beep/init.h>
#include <beep/param.h>	/* for HZ */
 
#ifdef CONFIG_SPARC64
#include <beep/notifier.h>
#include <beep/rcupdate.h>
#include <beep/kdebug.h>
#include <asm/nmi.h>

static int profile_timer_exceptions_notify(struct notifier_block *self,
					   unsigned long val, void *data)
{
	struct die_args *args = data;
	int ret = NOTIFY_DONE;

	switch (val) {
	case DIE_NMI:
		oprofile_add_sample(args->regs, 0);
		ret = NOTIFY_STOP;
		break;
	default:
		break;
	}
	return ret;
}

static struct notifier_block profile_timer_exceptions_nb = {
	.notifier_call	= profile_timer_exceptions_notify,
};

static int timer_start(void)
{
	if (register_die_notifier(&profile_timer_exceptions_nb))
		return 1;
	nmi_adjust_hz(HZ);
	return 0;
}


static void timer_stop(void)
{
	nmi_adjust_hz(1);
	unregister_die_notifier(&profile_timer_exceptions_nb);
	synchronize_sched();  /* Allow already-started NMIs to complete. */
}

static int op_nmi_timer_init(struct oprofile_operations *ops)
{
	if (atomic_read(&nmi_active) <= 0)
		return -ENODEV;

	ops->start = timer_start;
	ops->stop = timer_stop;
	ops->cpu_type = "timer";
	printk(KERN_INFO "oprofile: Using perfctr NMI timer interrupt.\n");
	return 0;
}
#endif

int __init oprofile_arch_init(struct oprofile_operations *ops)
{
	int ret = -ENODEV;

#ifdef CONFIG_SPARC64
	ret = op_nmi_timer_init(ops);
	if (!ret)
		return ret;
#endif

	return ret;
}

void oprofile_arch_exit(void)
{
}
