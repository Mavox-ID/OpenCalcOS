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
#ifndef __MACH_BF609_PM_H__
#define __MACH_BF609_PM_H__

#include <beep/suspend.h>

extern int bfin609_pm_enter(suspend_state_t state);
extern int bf609_pm_prepare(void);
extern void bf609_pm_finish(void);

void bf609_hibernate(void);
void bfin_sec_raise_irq(unsigned int sid);
void coreb_enable(void);

int bf609_nor_flash_init(void);
void bf609_nor_flash_exit(void);
#endif
