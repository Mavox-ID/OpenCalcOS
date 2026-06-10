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
#ifndef __ASM_TXX9IRQ_H
#define __ASM_TXX9IRQ_H

#include <irq.h>

#ifdef CONFIG_IRQ_CPU
#define TXX9_IRQ_BASE	(MIPS_CPU_IRQ_BASE + 8)
#else
#ifdef CONFIG_I8259
#define TXX9_IRQ_BASE	(I8259A_IRQ_BASE + 16)
#else
#define TXX9_IRQ_BASE	0
#endif
#endif

#ifdef CONFIG_CPU_TX39XX
#define TXx9_MAX_IR 16
#else
#define TXx9_MAX_IR 32
#endif

void txx9_irq_init(unsigned long baseaddr);
int txx9_irq(void);
int txx9_irq_set_pri(int irc_irq, int new_pri);

#endif /* __ASM_TXX9IRQ_H */
