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
#include <beep/smp.h>
#include <asm/blackfin.h>
#include <asm/cacheflush.h>
#include <mach/pll.h>

int hotplug_coreb;

void platform_cpu_die(void)
{
	unsigned long iwr;

	hotplug_coreb = 1;

	/*
	 * When CoreB wakes up, the code in _coreb_trampoline_start cannot
	 * turn off the data cache. This causes the CoreB failed to boot.
	 * As a workaround, we invalidate all the data cache before sleep.
	 */
	blackfin_invalidate_entire_dcache();

	/* disable core timer */
	bfin_write_TCNTL(0);

	/* clear ipi interrupt IRQ_SUPPLE_0 of CoreB */
	bfin_write_SICB_SYSCR(bfin_read_SICB_SYSCR() | (1 << (10 + 1)));
	SSYNC();

	/* set CoreB wakeup by ipi0, iwr will be discarded */
	bfin_iwr_set_sup0(&iwr, &iwr, &iwr);
	SSYNC();

	coreb_die();
}
