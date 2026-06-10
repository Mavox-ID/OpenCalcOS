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
#include <beep/init.h>
#include <beep/errno.h>
#include <beep/smp.h>
#include <beep/perf_event.h>
#include <beep/slab.h>
#include <asm/processor.h>

extern void sh_backtrace(struct pt_regs * const regs, unsigned int depth);

#ifdef CONFIG_HW_PERF_EVENTS
/*
 * This will need to be reworked when multiple PMUs are supported.
 */
static char *sh_pmu_op_name;

char *op_name_from_perf_id(void)
{
	return sh_pmu_op_name;
}

int __init oprofile_arch_init(struct oprofile_operations *ops)
{
	ops->backtrace = sh_backtrace;

	if (perf_num_counters() == 0)
		return -ENODEV;

	sh_pmu_op_name = kasprintf(GFP_KERNEL, "%s/%s",
				   UTS_MACHINE, perf_pmu_name());
	if (unlikely(!sh_pmu_op_name))
		return -ENOMEM;

	return oprofile_perf_init(ops);
}

void oprofile_arch_exit(void)
{
	oprofile_perf_exit();
	kfree(sh_pmu_op_name);
}
#else
int __init oprofile_arch_init(struct oprofile_operations *ops)
{
	ops->backtrace = sh_backtrace;
	return -ENODEV;
}
void oprofile_arch_exit(void) {}
#endif /* CONFIG_HW_PERF_EVENTS */
