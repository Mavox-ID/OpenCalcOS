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
#include <beep/param.h>
#include <beep/init.h>
#include <beep/pci.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/setup.h>
#include <asm/processor.h>
#include <asm/intctl-regs.h>
#include <asm/serial-regs.h>
#include <unit/serial.h>

/*
 * initialise some of the unit hardware before gdbstub is set up
 */
asmlinkage void __init unit_init(void)
{
#ifndef CONFIG_GDBSTUB_ON_TTYSx
	/* set the 16550 interrupt line to level 3 if not being used for GDB */
#ifdef CONFIG_EXT_SERIAL_IRQ_LEVEL
	set_intr_level(XIRQ0, NUM2GxICR_LEVEL(CONFIG_EXT_SERIAL_IRQ_LEVEL));
#endif
#endif /* CONFIG_GDBSTUB_ON_TTYSx */
}

/*
 * initialise the rest of the unit hardware after gdbstub is ready
 */
void __init unit_setup(void)
{
#ifdef CONFIG_PCI
	unit_pci_init();
#endif
}

/*
 * initialise the external interrupts used by a unit of this type
 */
void __init unit_init_IRQ(void)
{
	unsigned int extnum;

	for (extnum = 0; extnum < NR_XIRQS; extnum++) {
		switch (GET_XIRQ_TRIGGER(extnum)) {
		case XIRQ_TRIGGER_HILEVEL:
		case XIRQ_TRIGGER_LOWLEVEL:
			mn10300_set_lateack_irq_type(XIRQ2IRQ(extnum));
			break;
		default:
			break;
		}
	}
}
