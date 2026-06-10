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
#ifndef __PUV3_PM_H__
#define __PUV3_PM_H__

#include <beep/suspend.h>

struct puv3_cpu_pm_fns {
	int	save_count;
	void	(*save)(unsigned long *);
	void	(*restore)(unsigned long *);
	int	(*valid)(suspend_state_t state);
	void	(*enter)(suspend_state_t state);
	int	(*prepare)(void);
	void	(*finish)(void);
};

extern struct puv3_cpu_pm_fns *puv3_cpu_pm_fns;

/* sleep.S */
extern void puv3_cpu_suspend(unsigned int);

extern void puv3_cpu_resume(void);

extern int puv3_pm_enter(suspend_state_t state);

/* Defined in hibernate_asm.S */
extern int restore_image(pgd_t *resume_pg_dir, struct pbe *restore_pblist);

/* References to section boundaries */
extern const void __nosave_begin, __nosave_end;

extern struct pbe *restore_pblist;
#endif
