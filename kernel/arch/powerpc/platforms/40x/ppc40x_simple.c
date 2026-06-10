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
#include <asm/machdep.h>
#include <asm/pci-bridge.h>
#include <asm/ppc4xx.h>
#include <asm/prom.h>
#include <asm/time.h>
#include <asm/udbg.h>
#include <asm/uic.h>

#include <beep/init.h>
#include <beep/of_platform.h>

static __initdata struct of_device_id ppc40x_of_bus[] = {
	{ .compatible = "ibm,plb3", },
	{ .compatible = "ibm,plb4", },
	{ .compatible = "ibm,opb", },
	{ .compatible = "ibm,ebc", },
	{ .compatible = "simple-bus", },
	{},
};

static int __init ppc40x_device_probe(void)
{
	of_platform_bus_probe(NULL, ppc40x_of_bus, NULL);

	return 0;
}
machine_device_initcall(ppc40x_simple, ppc40x_device_probe);

/* This is the list of boards that can be supported by this simple
 * platform code.  This does _not_ mean the boards are compatible,
 * as they most certainly are not from a device tree perspective.
 * However, their differences are handled by the device tree and the
 * drivers and therefore they don't need custom board support files.
 *
 * Again, if your board needs to do things differently then create a
 * board.c file for it rather than adding it to this list.
 */
static const char * const board[] __initconst = {
	"amcc,acadia",
	"amcc,haleakala",
	"amcc,kilauea",
	"amcc,makalu",
	"apm,klondike",
	"est,hotfoot",
	"plathome,obs600",
	NULL
};

static int __init ppc40x_probe(void)
{
	if (of_flat_dt_match(of_get_flat_dt_root(), board)) {
		pci_set_flags(PCI_REASSIGN_ALL_RSRC);
		return 1;
	}

	return 0;
}

define_machine(ppc40x_simple) {
	.name = "PowerPC 40x Platform",
	.probe = ppc40x_probe,
	.progress = udbg_progress,
	.init_IRQ = uic_init_tree,
	.get_irq = uic_get_irq,
	.restart = ppc4xx_reset_system,
	.calibrate_decr = generic_calibrate_decr,
};
