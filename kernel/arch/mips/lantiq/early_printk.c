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
#include <beep/cpu.h>
#include <lantiq_soc.h>

#define ASC_BUF		1024
#define LTQ_ASC_FSTAT	((u32 *)(LTQ_EARLY_ASC + 0x0048))
#ifdef __BIG_ENDIAN
#define LTQ_ASC_TBUF	((u32 *)(LTQ_EARLY_ASC + 0x0020 + 3))
#else
#define LTQ_ASC_TBUF	((u32 *)(LTQ_EARLY_ASC + 0x0020))
#endif
#define TXMASK		0x3F00
#define TXOFFSET	8

void prom_putchar(char c)
{
	unsigned long flags;

	local_irq_save(flags);
	do { } while ((ltq_r32(LTQ_ASC_FSTAT) & TXMASK) >> TXOFFSET);
	if (c == '\n')
		ltq_w8('\r', LTQ_ASC_TBUF);
	ltq_w8(c, LTQ_ASC_TBUF);
	local_irq_restore(flags);
}
