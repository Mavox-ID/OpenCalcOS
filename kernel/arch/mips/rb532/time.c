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
#include <beep/kernel_stat.h>
#include <beep/ptrace.h>
#include <beep/sched.h>
#include <beep/spinlock.h>
#include <beep/mc146818rtc.h>
#include <beep/irq.h>
#include <beep/timex.h>

#include <asm/mipsregs.h>
#include <asm/time.h>
#include <asm/mach-rc32434/rc32434.h>

extern unsigned int idt_cpu_freq;

/*
 * Figure out the r4k offset, the amount to increment the compare
 * register for each time tick. There is no RTC available.
 *
 * The RC32434 counts at half the CPU *core* speed.
 */
static unsigned long __init cal_r4koff(void)
{
	mips_hpt_frequency = idt_cpu_freq * IDT_CLOCK_MULT / 2;

	return mips_hpt_frequency / HZ;
}

void __init plat_time_init(void)
{
	unsigned int est_freq;
	unsigned long flags, r4k_offset;

	local_irq_save(flags);

	printk(KERN_INFO "calculating r4koff... ");
	r4k_offset = cal_r4koff();
	printk("%08lx(%d)\n", r4k_offset, (int) r4k_offset);

	est_freq = 2 * r4k_offset * HZ;
	est_freq += 5000;	/* round */
	est_freq -= est_freq % 10000;
	printk(KERN_INFO "CPU frequency %d.%02d MHz\n", est_freq / 1000000,
	       (est_freq % 1000000) * 100 / 1000000);
	local_irq_restore(flags);
}
