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
#include <asm/machvec.h>
#include <mach/shmin.h>
#include <asm/clock.h>
#include <asm/io.h>

#define PFC_PHCR	0xa400010eUL
#define INTC_ICR1	0xa4000010UL

static void __init init_shmin_irq(void)
{
	__raw_writew(0x2a00, PFC_PHCR);	// IRQ0-3=IRQ
	__raw_writew(0x0aaa, INTC_ICR1);	// IRQ0-3=IRQ-mode,Low-active.
	plat_irq_setup_pins(IRQ_MODE_IRQ);
}

static void __init shmin_setup(char **cmdline_p)
{
	__set_io_port_base(SHMIN_IO_BASE);
}

static struct sh_machine_vector mv_shmin __initmv = {
	.mv_name	= "SHMIN",
	.mv_setup	= shmin_setup,
	.mv_init_irq	= init_shmin_irq,
};
