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
#include <beep/irq.h>
#include <mach/fpga.h>
#include <mach/irq.h>

enum {
	ATA_IRQ_BIT		= 1,
	SPI_BUSY_BIT		= 2,
	LIRQ5_BIT		= 3,
	LIRQ6_BIT		= 4,
	LIRQ7_BIT		= 5,
	LIRQ8_BIT		= 6,
	KEY_IRQ_BIT		= 7,
	PEN_IRQ_BIT		= 8,
	ETH_IRQ_BIT		= 9,
	RTC_ALARM_BIT		= 10,
	CRYSTAL_FAIL_BIT	= 12,
	ETH_PME_BIT		= 14,
};

void __init sdk7786_init_irq(void)
{
	unsigned int tmp;

	/* Enable priority encoding for all IRLs */
	fpga_write_reg(fpga_read_reg(INTMSR) | 0x0303, INTMSR);

	/* Clear FPGA interrupt status registers */
	fpga_write_reg(0x0000, INTASR);
	fpga_write_reg(0x0000, INTBSR);

	/* Unmask FPGA interrupts */
	tmp = fpga_read_reg(INTAMR);
	tmp &= ~(1 << ETH_IRQ_BIT);
	fpga_write_reg(tmp, INTAMR);

	plat_irq_setup_pins(IRQ_MODE_IRL7654_MASK);
	plat_irq_setup_pins(IRQ_MODE_IRL3210_MASK);
}
