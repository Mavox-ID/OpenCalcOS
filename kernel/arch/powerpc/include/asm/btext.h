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
#ifndef __PPC_BTEXT_H
#define __PPC_BTEXT_H
#ifdef __KERNEL__

extern int btext_find_display(int allow_nonstdout);
extern void btext_update_display(unsigned long phys, int width, int height,
				 int depth, int pitch);
extern void btext_setup_display(int width, int height, int depth, int pitch,
				unsigned long address);
extern void btext_prepare_BAT(void);
extern void btext_unmap(void);

extern void btext_drawchar(char c);
extern void btext_drawstring(const char *str);
extern void btext_drawhex(unsigned long v);
extern void btext_drawtext(const char *c, unsigned int len);

extern void btext_clearscreen(void);
extern void btext_flushscreen(void);
extern void btext_flushline(void);

#endif /* __KERNEL__ */
#endif /* __PPC_BTEXT_H */
