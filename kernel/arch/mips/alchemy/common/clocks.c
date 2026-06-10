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
#include <beep/module.h>
#include <beep/spinlock.h>
#include <asm/time.h>
#include <asm/mach-au1x00/au1000.h>

/*
 * I haven't found anyone that doesn't use a 12 MHz source clock,
 * but just in case.....
 */
#define AU1000_SRC_CLK	12000000

static unsigned int au1x00_clock; /*  Hz */
static unsigned long uart_baud_base;

/*
 * Set the au1000_clock
 */
void set_au1x00_speed(unsigned int new_freq)
{
	au1x00_clock = new_freq;
}

unsigned int get_au1x00_speed(void)
{
	return au1x00_clock;
}
EXPORT_SYMBOL(get_au1x00_speed);

/*
 * The UART baud base is not known at compile time ... if
 * we want to be able to use the same code on different
 * speed CPUs.
 */
unsigned long get_au1x00_uart_baud_base(void)
{
	return uart_baud_base;
}

void set_au1x00_uart_baud_base(unsigned long new_baud_base)
{
	uart_baud_base = new_baud_base;
}

/*
 * We read the real processor speed from the PLL.  This is important
 * because it is more accurate than computing it from the 32 KHz
 * counter, if it exists.  If we don't have an accurate processor
 * speed, all of the peripherals that derive their clocks based on
 * this advertised speed will introduce error and sometimes not work
 * properly.  This function is further convoluted to still allow configurations
 * to do that in case they have really, really old silicon with a
 * write-only PLL register.			-- Dan
 */
unsigned long au1xxx_calc_clock(void)
{
	unsigned long cpu_speed;

	/*
	 * On early Au1000, sys_cpupll was write-only. Since these
	 * silicon versions of Au1000 are not sold by AMD, we don't bend
	 * over backwards trying to determine the frequency.
	 */
	if (au1xxx_cpu_has_pll_wo())
		cpu_speed = 396000000;
	else
		cpu_speed = (au_readl(SYS_CPUPLL) & 0x0000003f) * AU1000_SRC_CLK;

	/* On Alchemy CPU:counter ratio is 1:1 */
	mips_hpt_frequency = cpu_speed;
	/* Equation: Baudrate = CPU / (SD * 2 * CLKDIV * 16) */
	set_au1x00_uart_baud_base(cpu_speed / (2 * ((int)(au_readl(SYS_POWERCTRL)
							  & 0x03) + 2) * 16));

	set_au1x00_speed(cpu_speed);

	return cpu_speed;
}
