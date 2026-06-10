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
#include <beep/interrupt.h>
#include <beep/irq.h>

#include <asm/gt64120.h>
#include <asm/time.h>

#define WRPPMC_CPU_CLK_FREQ 40000000 /* 40MHZ */

/*
 * Estimate CPU frequency.  Sets mips_hpt_frequency as a side-effect
 *
 * NOTE: We disable all GT64120 timers, and use MIPS processor internal
 * timer as the source of kernel clock tick.
 */
void __init plat_time_init(void)
{
	/* Disable GT64120 timers */
	GT_WRITE(GT_TC_CONTROL_OFS, 0x00);
	GT_WRITE(GT_TC0_OFS, 0x00);
	GT_WRITE(GT_TC1_OFS, 0x00);
	GT_WRITE(GT_TC2_OFS, 0x00);
	GT_WRITE(GT_TC3_OFS, 0x00);

	/* Use MIPS compare/count internal timer */
	mips_hpt_frequency = WRPPMC_CPU_CLK_FREQ;
}
