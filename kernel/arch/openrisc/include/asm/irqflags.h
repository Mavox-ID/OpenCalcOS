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
#ifndef ___ASM_OPENRISC_IRQFLAGS_H
#define ___ASM_OPENRISC_IRQFLAGS_H

#include <asm/spr_defs.h>

#define ARCH_IRQ_DISABLED        0x00
#define ARCH_IRQ_ENABLED         (SPR_SR_IEE|SPR_SR_TEE)

#include <asm-generic/irqflags.h>

#endif /* ___ASM_OPENRISC_IRQFLAGS_H */
