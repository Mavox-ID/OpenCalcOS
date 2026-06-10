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

#include <asm/cacheflush.h>

#include "core.h"
#include "sysregs.h"

extern void secondary_startup(void);

/*
 * platform-specific code to shutdown a CPU
 *
 */
void __ref highbank_cpu_die(unsigned int cpu)
{
	flush_cache_all();

	highbank_set_cpu_jump(cpu, phys_to_virt(0));
	highbank_set_core_pwr();

	cpu_do_idle();

	/* We should never return from idle */
	panic("highbank: cpu %d unexpectedly exit from shutdown\n", cpu);
}
