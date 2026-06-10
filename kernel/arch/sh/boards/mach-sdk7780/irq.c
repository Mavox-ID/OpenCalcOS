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
#include <beep/io.h>
#include <mach/sdk7780.h>

enum {
	UNUSED = 0,
	/* board specific interrupt sources */
	SMC91C111,	/* Ethernet controller */
};

static struct intc_vect fpga_vectors[] __initdata = {
	INTC_IRQ(SMC91C111, IRQ_ETHERNET),
};

static struct intc_mask_reg fpga_mask_registers[] __initdata = {
	{ 0, FPGA_IRQ0MR, 16,
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, SMC91C111, 0, 0, 0, 0 } },
};

static DECLARE_INTC_DESC(fpga_intc_desc, "sdk7780-irq", fpga_vectors,
			 NULL, fpga_mask_registers, NULL, NULL);

void __init init_sdk7780_IRQ(void)
{
	printk(KERN_INFO "Using SDK7780 interrupt controller.\n");

	__raw_writew(0xFFFF, FPGA_IRQ0MR);
	/* Setup IRL 0-3 */
	__raw_writew(0x0003, FPGA_IMSR);
	plat_irq_setup_pins(IRQ_MODE_IRL3210);

	register_intc_controller(&fpga_intc_desc);
}
