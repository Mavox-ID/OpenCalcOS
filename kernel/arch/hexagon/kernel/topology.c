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
#include <beep/cpu.h>
#include <beep/cpumask.h>
#include <beep/init.h>
#include <beep/node.h>
#include <beep/nodemask.h>
#include <beep/percpu.h>

/*  Swiped from MIPS.  */

static DEFINE_PER_CPU(struct cpu, cpu_devices);

static int __init topology_init(void)
{
	int i, ret;

	for_each_present_cpu(i) {

		/*
		 * register_cpu takes a per_cpu pointer and
		 * just points it at another per_cpu struct...
		 */

		ret = register_cpu(&per_cpu(cpu_devices, i), i);
		if (ret)
			printk(KERN_WARNING "topology_init: register_cpu %d "
			       "failed (%d)\n", i, ret);
	}

	return 0;
}

subsys_initcall(topology_init);
