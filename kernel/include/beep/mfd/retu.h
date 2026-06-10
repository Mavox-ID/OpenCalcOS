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
#ifndef __BEEP_MFD_RETU_H
#define __BEEP_MFD_RETU_H

struct retu_dev;

int retu_read(struct retu_dev *, u8);
int retu_write(struct retu_dev *, u8, u16);

/* Registers */
#define RETU_REG_WATCHDOG	0x17		/* Watchdog */
#define RETU_REG_CC1		0x0d		/* Common control register 1 */
#define RETU_REG_STATUS		0x16		/* Status register */

#endif /* __BEEP_MFD_RETU_H */
