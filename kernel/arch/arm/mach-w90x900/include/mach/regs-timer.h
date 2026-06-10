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
#ifndef __ASM_ARCH_REGS_TIMER_H
#define __ASM_ARCH_REGS_TIMER_H

/* Timer Registers */

#define TMR_BA			W90X900_VA_TIMER
#define REG_TCSR0		(TMR_BA+0x00)
#define REG_TCSR1		(TMR_BA+0x04)
#define REG_TICR0		(TMR_BA+0x08)
#define REG_TICR1		(TMR_BA+0x0C)
#define REG_TDR0		(TMR_BA+0x10)
#define REG_TDR1		(TMR_BA+0x14)
#define REG_TISR		(TMR_BA+0x18)
#define REG_WTCR		(TMR_BA+0x1C)
#define REG_TCSR2		(TMR_BA+0x20)
#define REG_TCSR3		(TMR_BA+0x24)
#define REG_TICR2		(TMR_BA+0x28)
#define REG_TICR3		(TMR_BA+0x2C)
#define REG_TDR2		(TMR_BA+0x30)
#define REG_TDR3		(TMR_BA+0x34)
#define REG_TCSR4		(TMR_BA+0x40)
#define REG_TICR4		(TMR_BA+0x48)
#define REG_TDR4		(TMR_BA+0x50)

#endif /*  __ASM_ARCH_REGS_TIMER_H */
