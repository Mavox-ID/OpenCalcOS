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
#ifndef __ASM_AVR32_ARCH_PM_H
#define __ASM_AVR32_ARCH_PM_H

/* Possible arguments to the "sleep" instruction */
#define CPU_SLEEP_IDLE		0
#define CPU_SLEEP_FROZEN	1
#define CPU_SLEEP_STANDBY	2
#define CPU_SLEEP_STOP		3
#define CPU_SLEEP_STATIC	5

#ifndef __ASSEMBLY__
extern void cpu_enter_idle(void);
extern void cpu_enter_standby(unsigned long sdramc_base);

extern bool disable_idle_sleep;

static inline void cpu_disable_idle_sleep(void)
{
	disable_idle_sleep = true;
}

static inline void cpu_enable_idle_sleep(void)
{
	disable_idle_sleep = false;
}

static inline void cpu_idle_sleep(void)
{
	/*
	 * If we're using the COUNT and COMPARE registers for
	 * timekeeping, we can't use the IDLE state.
	 */
	if (disable_idle_sleep)
		cpu_relax();
	else
		cpu_enter_idle();
}

void intc_set_suspend_handler(unsigned long offset);
#endif

#endif /* __ASM_AVR32_ARCH_PM_H */
