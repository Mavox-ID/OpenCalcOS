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
#include <beep/interrupt.h>
#include <beep/linkage.h>

#include <asm/addrspace.h>

typedef void __noreturn (* noret_func_t)(void);

static inline void __noreturn back_to_prom(void)
{
	noret_func_t func = (void *)CKSEG1ADDR(0x1fc00000);

	func();
}

void __noreturn dec_machine_restart(char *command)
{
	back_to_prom();
}

void __noreturn dec_machine_halt(void)
{
	back_to_prom();
}

void __noreturn dec_machine_power_off(void)
{
    /* DECstations don't have a software power switch */
	back_to_prom();
}

irqreturn_t dec_intr_halt(int irq, void *dev_id)
{
	dec_machine_halt();
}
