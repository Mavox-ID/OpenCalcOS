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
#ifndef __ASM_ARCH_IRQS_H
#define __ASM_ARCH_IRQS_H

#include <mach/irqs-eb.h>
#include <mach/irqs-pb11mp.h>
#include <mach/irqs-pb1176.h>
#include <mach/irqs-pba8.h>
#include <mach/irqs-pbx.h>

#define IRQ_LOCALTIMER		29
#define IRQ_LOCALWDOG		30

#define IRQ_GIC_START		32

#ifndef NR_IRQS
#error "NR_IRQS not defined by the board-specific files"
#endif

#endif
