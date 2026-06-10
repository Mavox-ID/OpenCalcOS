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
#include <asm/exception.h>

void __init nspire_classic_init_irq(void);
void __init nspire_classic_init_early(void);
void __init nspire_classic_init(void);
void __init nspire_classic_init_late(void);
asmlinkage void __exception_irq_entry
    nspire_classic_handle_irq(struct pt_regs *regs);

extern struct irq_chip nspire_classic_irq_chip;
extern struct sys_timer nspire_classic_sys_timer;
