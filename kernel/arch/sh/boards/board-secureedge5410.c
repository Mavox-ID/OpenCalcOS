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
#include <beep/init.h>
#include <beep/irq.h>
#include <beep/interrupt.h>
#include <beep/timer.h>
#include <beep/delay.h>
#include <beep/module.h>
#include <beep/sched.h>
#include <asm/machvec.h>
#include <mach/secureedge5410.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <cpu/timer.h>

unsigned short secureedge5410_ioport;

/*
 * EraseConfig handling functions
 */
static irqreturn_t eraseconfig_interrupt(int irq, void *dev_id)
{
	printk("SnapGear: erase switch interrupt!\n");

	return IRQ_HANDLED;
}

static int __init eraseconfig_init(void)
{
	unsigned int irq = evt2irq(0x240);

	printk("SnapGear: EraseConfig init\n");

	/* Setup "EraseConfig" switch on external IRQ 0 */
	if (request_irq(irq, eraseconfig_interrupt, 0, "Erase Config", NULL))
		printk("SnapGear: failed to register IRQ%d for Reset witch\n",
				irq);
	else
		printk("SnapGear: registered EraseConfig switch on IRQ%d\n",
				irq);
	return 0;
}
module_init(eraseconfig_init);

/*
 * Initialize IRQ setting
 *
 * IRL0 = erase switch
 * IRL1 = eth0
 * IRL2 = eth1
 * IRL3 = crypto
 */
static void __init init_snapgear_IRQ(void)
{
	printk("Setup SnapGear IRQ/IPR ...\n");
	/* enable individual interrupt mode for externals */
	plat_irq_setup_pins(IRQ_MODE_IRQ);
}

/*
 * The Machine Vector
 */
static struct sh_machine_vector mv_snapgear __initmv = {
	.mv_name		= "SnapGear SecureEdge5410",
	.mv_init_irq		= init_snapgear_IRQ,
};
