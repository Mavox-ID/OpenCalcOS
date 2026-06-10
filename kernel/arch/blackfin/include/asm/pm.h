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
#ifndef __PM_H__
#define __PM_H__

#include <beep/suspend.h>

struct bfin_cpu_pm_fns {
	void    (*save)(unsigned long *);
	void    (*restore)(unsigned long *);
	int     (*valid)(suspend_state_t state);
	void    (*enter)(suspend_state_t state);
	int     (*prepare)(void);
	void    (*finish)(void);
};

extern struct bfin_cpu_pm_fns *bfin_cpu_pm;

# ifdef CONFIG_BFIN_COREB
void bfin_coreb_start(void);
void bfin_coreb_stop(void);
void bfin_coreb_reset(void);
# endif

#endif
