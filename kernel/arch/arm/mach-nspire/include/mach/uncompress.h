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
#ifndef NSPIRE_UNCOMPRESS_H
#define NSPIRE_UNCOMPRESS_H

#include <mach/nspire_mmio.h>

#define OFFSET_VAL(var, offset) ((var)[(offset)>>2])
static inline void putc(int c)
{
	volatile unsigned __attribute__((unused)) *serial_base =
		(volatile unsigned *) NSPIRE_APB_PHYS(NSPIRE_APB_UART);

#ifdef CONFIG_NSPIRE_EARLYPRINTK_CLASSIC
	OFFSET_VAL(serial_base, 0x00) = (unsigned char)c;
	while (! (OFFSET_VAL(serial_base, 0x14) & (1<<5)) ) barrier();
#endif

#ifdef CONFIG_NSPIRE_EARLYPRINTK_CX
	OFFSET_VAL(serial_base, 0x00) = (unsigned char)c;
	while (OFFSET_VAL(serial_base, 0x18) & (1<<5)) barrier();
#endif

}
#undef OFFSET_VAL

#define arch_decomp_setup()
#define flush()

#endif
