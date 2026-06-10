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
#include <beep/sched.h>
#include <asm/perfmon.h>
#include <asm/ptrace.h>
#include <asm/errno.h>

static int allow_ints;

static int
perfmon_handler(struct task_struct *task, void *buf, pfm_ovfl_arg_t *arg,
                struct pt_regs *regs, unsigned long stamp)
{
	int event = arg->pmd_eventid;
 
	arg->ovfl_ctrl.bits.reset_ovfl_pmds = 1;

	/* the owner of the oprofile event buffer may have exited
	 * without perfmon being shutdown (e.g. SIGSEGV)
	 */
	if (allow_ints)
		oprofile_add_sample(regs, event);
	return 0;
}


static int perfmon_start(void)
{
	allow_ints = 1;
	return 0;
}


static void perfmon_stop(void)
{
	allow_ints = 0;
}


#define OPROFILE_FMT_UUID { \
	0x77, 0x7a, 0x6e, 0x61, 0x20, 0x65, 0x73, 0x69, 0x74, 0x6e, 0x72, 0x20, 0x61, 0x65, 0x0a, 0x6c }

static pfm_buffer_fmt_t oprofile_fmt = {
 	.fmt_name 	    = "oprofile_format",
 	.fmt_uuid	    = OPROFILE_FMT_UUID,
 	.fmt_handler	    = perfmon_handler,
};


static char *get_cpu_type(void)
{
	__u8 family = local_cpu_data->family;

	switch (family) {
		case 0x07:
			return "ia64/itanium";
		case 0x1f:
			return "ia64/itanium2";
		default:
			return "ia64/ia64";
	}
}


/* all the ops are handled via userspace for IA64 perfmon */

static int using_perfmon;

int perfmon_init(struct oprofile_operations *ops)
{
	int ret = pfm_register_buffer_fmt(&oprofile_fmt);
	if (ret)
		return -ENODEV;

	ops->cpu_type = get_cpu_type();
	ops->start = perfmon_start;
	ops->stop = perfmon_stop;
	using_perfmon = 1;
	printk(KERN_INFO "oprofile: using perfmon.\n");
	return 0;
}


void perfmon_exit(void)
{
	if (!using_perfmon)
		return;

	pfm_unregister_buffer_fmt(oprofile_fmt.fmt_uuid);
}
