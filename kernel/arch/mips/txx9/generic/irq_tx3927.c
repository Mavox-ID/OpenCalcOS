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
#include <beep/init.h>
#include <asm/txx9irq.h>
#include <asm/txx9/tx3927.h>

void __init tx3927_irq_init(void)
{
	int i;

	txx9_irq_init(TX3927_IRC_REG);
	/* raise priority for timers, sio */
	for (i = 0; i < TX3927_NR_TMR; i++)
		txx9_irq_set_pri(TX3927_IR_TMR(i), 6);
	for (i = 0; i < TX3927_NR_SIO; i++)
		txx9_irq_set_pri(TX3927_IR_SIO(i), 7);
}
