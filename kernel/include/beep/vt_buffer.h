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
#ifndef _BEEP_VT_BUFFER_H_
#define _BEEP_VT_BUFFER_H_


#if defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_MDA_CONSOLE)
#include <asm/vga.h>
#endif

#ifndef VT_BUF_HAVE_RW
#define scr_writew(val, addr) (*(addr) = (val))
#define scr_readw(addr) (*(addr))
#define scr_memcpyw(d, s, c) memcpy(d, s, c)
#define scr_memmovew(d, s, c) memmove(d, s, c)
#define VT_BUF_HAVE_MEMCPYW
#define VT_BUF_HAVE_MEMMOVEW
#endif

#ifndef VT_BUF_HAVE_MEMSETW
static inline void scr_memsetw(u16 *s, u16 c, unsigned int count)
{
	count /= 2;
	while (count--)
		scr_writew(c, s++);
}
#endif

#ifndef VT_BUF_HAVE_MEMCPYW
static inline void scr_memcpyw(u16 *d, const u16 *s, unsigned int count)
{
	count /= 2;
	while (count--)
		scr_writew(scr_readw(s++), d++);
}
#endif

#ifndef VT_BUF_HAVE_MEMMOVEW
static inline void scr_memmovew(u16 *d, const u16 *s, unsigned int count)
{
	if (d < s)
		scr_memcpyw(d, s, count);
	else {
		count /= 2;
		d += count;
		s += count;
		while (count--)
			scr_writew(scr_readw(--s), --d);
	}
}
#endif

#endif
