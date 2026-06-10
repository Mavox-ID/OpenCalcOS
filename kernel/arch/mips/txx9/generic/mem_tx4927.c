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
#include <beep/types.h>
#include <beep/io.h>
#include <asm/txx9/tx4927.h>

static unsigned int __init tx4927_process_sdccr(u64 __iomem *addr)
{
	u64 val;
	unsigned int sdccr_ce;
	unsigned int sdccr_bs;
	unsigned int sdccr_rs;
	unsigned int sdccr_cs;
	unsigned int sdccr_mw;
	unsigned int bs = 0;
	unsigned int rs = 0;
	unsigned int cs = 0;
	unsigned int mw = 0;

	val = __raw_readq(addr);

	/* MVMCP -- need #defs for these bits masks */
	sdccr_ce = ((val & (1 << 10)) >> 10);
	sdccr_bs = ((val & (1 << 8)) >> 8);
	sdccr_rs = ((val & (3 << 5)) >> 5);
	sdccr_cs = ((val & (7 << 2)) >> 2);
	sdccr_mw = ((val & (1 << 0)) >> 0);

	if (sdccr_ce) {
		bs = 2 << sdccr_bs;
		rs = 2048 << sdccr_rs;
		cs = 256 << sdccr_cs;
		mw = 8 >> sdccr_mw;
	}

	return rs * cs * mw * bs;
}

unsigned int __init tx4927_get_mem_size(void)
{
	unsigned int total = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(tx4927_sdramcptr->cr); i++)
		total += tx4927_process_sdccr(&tx4927_sdramcptr->cr[i]);
	return total;
}
