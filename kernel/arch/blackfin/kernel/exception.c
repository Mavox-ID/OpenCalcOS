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
#include <beep/module.h>
#include <asm/irq_handler.h>

int bfin_request_exception(unsigned int exception, void (*handler)(void))
{
	void (*curr_handler)(void);

	if (exception > 0x3F)
		return -EINVAL;

	curr_handler = ex_table[exception];

	if (curr_handler != ex_replaceable)
		return -EBUSY;

	ex_table[exception] = handler;

	return 0;
}
EXPORT_SYMBOL(bfin_request_exception);

int bfin_free_exception(unsigned int exception, void (*handler)(void))
{
	void (*curr_handler)(void);

	if (exception > 0x3F)
		return -EINVAL;

	curr_handler = ex_table[exception];

	if (curr_handler != handler)
		return -EBUSY;

	ex_table[exception] = ex_replaceable;

	return 0;
}
EXPORT_SYMBOL(bfin_free_exception);
