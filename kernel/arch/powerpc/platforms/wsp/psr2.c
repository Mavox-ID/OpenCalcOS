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
#include <beep/delay.h>
#include <beep/init.h>
#include <beep/irq.h>
#include <beep/kernel.h>
#include <beep/mm.h>
#include <beep/of.h>
#include <beep/smp.h>
#include <beep/time.h>

#include <asm/machdep.h>
#include <asm/udbg.h>

#include "ics.h"
#include "wsp.h"


static void psr2_spin(void)
{
	hard_irq_disable();
	for (;;)
		continue;
}

static void psr2_restart(char *cmd)
{
	psr2_spin();
}

static int __init psr2_probe(void)
{
	unsigned long root = of_get_flat_dt_root();

	if (of_flat_dt_is_compatible(root, "ibm,wsp-chroma")) {
		/* chroma systems also claim they are psr2s */
		return 0;
	}

	if (!of_flat_dt_is_compatible(root, "ibm,psr2"))
		return 0;

	return 1;
}

define_machine(psr2_md) {
	.name			= "PSR2 A2",
	.probe			= psr2_probe,
	.setup_arch		= wsp_setup_arch,
	.restart		= psr2_restart,
	.power_off		= psr2_spin,
	.halt			= psr2_spin,
	.calibrate_decr		= generic_calibrate_decr,
	.init_IRQ		= wsp_setup_irq,
	.progress		= udbg_progress,
	.power_save		= book3e_idle,
};

machine_arch_initcall(psr2_md, wsp_probe_devices);
