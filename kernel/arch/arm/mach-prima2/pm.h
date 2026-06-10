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
#ifndef _MACH_PRIMA2_PM_H_
#define _MACH_PRIMA2_PM_H_

#define SIRFSOC_PWR_SLEEPFORCE		0x01

#define SIRFSOC_SLEEP_MODE_MASK         0x3
#define SIRFSOC_DEEP_SLEEP_MODE         0x1

#define SIRFSOC_PWRC_PDN_CTRL           0x0
#define SIRFSOC_PWRC_PON_OFF            0x4
#define SIRFSOC_PWRC_TRIGGER_EN         0x8
#define SIRFSOC_PWRC_PIN_STATUS         0x14
#define SIRFSOC_PWRC_SCRATCH_PAD1       0x18
#define SIRFSOC_PWRC_SCRATCH_PAD2       0x1C

#ifndef __ASSEMBLY__
extern int sirfsoc_finish_suspend(unsigned long);
#endif

#endif

