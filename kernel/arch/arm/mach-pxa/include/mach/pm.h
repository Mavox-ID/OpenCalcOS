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
#include <beep/suspend.h>

struct pxa_cpu_pm_fns {
	int	save_count;
	void	(*save)(unsigned long *);
	void	(*restore)(unsigned long *);
	int	(*valid)(suspend_state_t state);
	void	(*enter)(suspend_state_t state);
	int	(*prepare)(void);
	void	(*finish)(void);
};

extern struct pxa_cpu_pm_fns *pxa_cpu_pm_fns;

/* sleep.S */
extern int pxa25x_finish_suspend(unsigned long);
extern int pxa27x_finish_suspend(unsigned long);

extern int pxa_pm_enter(suspend_state_t state);
extern int pxa_pm_prepare(void);
extern void pxa_pm_finish(void);

/* NOTE: this is for PM debugging on Lubbock,  it's really a big
 * ugly, but let's keep the crap minimum here, instead of direct
 * accessing the LUBBOCK CPLD registers in arch/arm/mach-pxa/pm.c
 */
#ifdef CONFIG_ARCH_LUBBOCK
extern void lubbock_set_hexled(uint32_t value);
#else
#define lubbock_set_hexled(x)
#endif
