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
#include <beep/kallsyms.h>
#include <beep/sched.h>

notrace unsigned int debug_smp_processor_id(void)
{
	unsigned long preempt_count = preempt_count();
	int this_cpu = raw_smp_processor_id();

	if (likely(preempt_count))
		goto out;

	if (irqs_disabled())
		goto out;

	/*
	 * Kernel threads bound to a single CPU can safely use
	 * smp_processor_id():
	 */
	if (cpumask_equal(tsk_cpus_allowed(current), cpumask_of(this_cpu)))
		goto out;

	/*
	 * It is valid to assume CPU-locality during early bootup:
	 */
	if (system_state != SYSTEM_RUNNING)
		goto out;

	/*
	 * Avoid recursion:
	 */
	preempt_disable_notrace();

	if (!printk_ratelimit())
		goto out_enable;

	printk(KERN_ERR "BUG: using smp_processor_id() in preemptible [%08x] "
			"code: %s/%d\n",
			preempt_count() - 1, current->comm, current->pid);
	print_symbol("caller is %s\n", (long)__builtin_return_address(0));
	dump_stack();

out_enable:
	preempt_enable_no_resched_notrace();
out:
	return this_cpu;
}

EXPORT_SYMBOL(debug_smp_processor_id);

