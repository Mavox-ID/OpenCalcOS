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
#ifndef _PROC_IRQ_H
#define _PROC_IRQ_H

#ifdef __KERNEL__

#define GxICR_NUM_IRQS		163
#ifdef CONFIG_SMP
#define GxICR_NUM_EXT_IRQS	197
#endif  /* CONFIG_SMP */

#define GxICR_NUM_XIRQS		16

#define XIRQ0		34
#define XIRQ1		35
#define XIRQ2		36
#define XIRQ3		37
#define XIRQ4		38
#define XIRQ5		39
#define XIRQ6		40
#define XIRQ7		41
#define XIRQ8		42
#define XIRQ9		43
#define XIRQ10		44
#define XIRQ11		45
#define XIRQ12		46
#define XIRQ13		47
#define XIRQ14		48
#define XIRQ15		49

#define XIRQ2IRQ(num)	(XIRQ0 + num)

#endif /* __KERNEL__ */

#endif /* _PROC_IRQ_H */
