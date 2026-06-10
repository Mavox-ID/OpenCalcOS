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
#include <beep/io.h>
#include <mach-se/mach/se7721.h>

enum {
	UNUSED = 0,

	/* board specific interrupt sources */
	MRSHPC,
};

static struct intc_vect vectors[] __initdata = {
	INTC_IRQ(MRSHPC, MRSHPC_IRQ0),
};

static struct intc_prio_reg prio_registers[] __initdata = {
	{ FPGA_ILSR6, 0, 8, 4, /* IRLMSK */
	  { 0, MRSHPC } },
};

static DECLARE_INTC_DESC(intc_desc, "SE7721", vectors,
			 NULL, NULL, prio_registers, NULL);

/*
 * Initialize IRQ setting
 */
void __init init_se7721_IRQ(void)
{
	/* PPCR */
	__raw_writew(__raw_readw(0xa4050118) & ~0x00ff, 0xa4050118);

	register_intc_controller(&intc_desc);
	intc_set_priority(MRSHPC_IRQ0, 0xf - MRSHPC_IRQ0);
}
