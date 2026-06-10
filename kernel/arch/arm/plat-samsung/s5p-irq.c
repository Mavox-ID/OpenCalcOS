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
#include <beep/interrupt.h>
#include <beep/irq.h>
#include <beep/io.h>

#include <asm/hardware/vic.h>

#include <mach/map.h>
#include <plat/regs-timer.h>
#include <plat/cpu.h>
#include <plat/irq-vic-timer.h>

void __init s5p_init_irq(u32 *vic, u32 num_vic)
{
#ifdef CONFIG_ARM_VIC
	int irq;

	/* initialize the VICs */
	for (irq = 0; irq < num_vic; irq++)
		vic_init(VA_VIC(irq), VIC_BASE(irq), vic[irq], 0);
#endif

	s3c_init_vic_timer_irq(5, IRQ_TIMER0);
}
