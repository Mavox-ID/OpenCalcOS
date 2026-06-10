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
#ifndef __ASM_IRQ_REGS_H
#define __ASM_IRQ_REGS_H

#define ARCH_HAS_OWN_IRQ_REGS

#include <beep/thread_info.h>

static inline struct pt_regs *get_irq_regs(void)
{
	return current_thread_info()->regs;
}

#endif /* __ASM_IRQ_REGS_H */
