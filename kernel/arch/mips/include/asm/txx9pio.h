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
#ifndef __ASM_TXX9PIO_H
#define __ASM_TXX9PIO_H

#include <beep/types.h>

struct txx9_pio_reg {
	__u32 dout;
	__u32 din;
	__u32 dir;
	__u32 od;
	__u32 flag[2];
	__u32 pol;
	__u32 intc;
	__u32 maskcpu;
	__u32 maskext;
};

int txx9_gpio_init(unsigned long baseaddr,
		   unsigned int base, unsigned int num);

#endif /* __ASM_TXX9PIO_H */
