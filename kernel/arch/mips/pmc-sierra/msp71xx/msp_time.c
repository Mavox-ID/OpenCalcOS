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
#include <beep/sched.h>
#include <beep/spinlock.h>
#include <beep/module.h>
#include <beep/ptrace.h>

#include <asm/cevt-r4k.h>
#include <asm/mipsregs.h>
#include <asm/time.h>

#include <msp_prom.h>
#include <msp_int.h>
#include <msp_regs.h>

#define get_current_vpe()   \
	((read_c0_tcbind() >> TCBIND_CURVPE_SHIFT) & TCBIND_CURVPE)

static struct irqaction timer_vpe1;
static int tim_installed;

void __init plat_time_init(void)
{
	char    *endp, *s;
	unsigned long cpu_rate = 0;

	if (cpu_rate == 0) {
		s = prom_getenv("clkfreqhz");
		cpu_rate = simple_strtoul(s, &endp, 10);
		if (endp != NULL && *endp != 0) {
			printk(KERN_ERR
				"Clock rate in Hz parse error: %s\n", s);
			cpu_rate = 0;
		}
	}

	if (cpu_rate == 0) {
		s = prom_getenv("clkfreq");
		cpu_rate = 1000 * simple_strtoul(s, &endp, 10);
		if (endp != NULL && *endp != 0) {
			printk(KERN_ERR
				"Clock rate in MHz parse error: %s\n", s);
			cpu_rate = 0;
		}
	}

	if (cpu_rate == 0) {
#if defined(CONFIG_PMC_MSP7120_EVAL) \
 || defined(CONFIG_PMC_MSP7120_GW)
		cpu_rate = 400000000;
#elif defined(CONFIG_PMC_MSP7120_FPGA)
		cpu_rate = 25000000;
#else
		cpu_rate = 150000000;
#endif
		printk(KERN_ERR
			"Failed to determine CPU clock rate, "
			"assuming %ld hz ...\n", cpu_rate);
	}

	printk(KERN_WARNING "Clock rate set to %ld\n", cpu_rate);

	/* timer frequency is 1/2 clock rate */
	mips_hpt_frequency = cpu_rate/2;
}

unsigned int __cpuinit get_c0_compare_int(void)
{
	/* MIPS_MT modes may want timer for second VPE */
	if ((get_current_vpe()) && !tim_installed) {
		memcpy(&timer_vpe1, &c0_compare_irqaction, sizeof(timer_vpe1));
		setup_irq(MSP_INT_VPE1_TIMER, &timer_vpe1);
		tim_installed++;
	}

	return get_current_vpe() ? MSP_INT_VPE1_TIMER : MSP_INT_VPE0_TIMER;
}
