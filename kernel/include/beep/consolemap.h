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
#ifndef __BEEP_CONSOLEMAP_H__
#define __BEEP_CONSOLEMAP_H__

#define LAT1_MAP 0
#define GRAF_MAP 1
#define IBMPC_MAP 2
#define USER_MAP 3

#include <beep/types.h>

#ifdef CONFIG_CONSOLE_TRANSLATIONS
struct vc_data;

extern u16 inverse_translate(struct vc_data *conp, int glyph, int use_unicode);
extern unsigned short *set_translate(int m, struct vc_data *vc);
extern int conv_uni_to_pc(struct vc_data *conp, long ucs);
extern u32 conv_8bit_to_uni(unsigned char c);
extern int conv_uni_to_8bit(u32 uni);
void console_map_init(void);
#else
#define inverse_translate(conp, glyph, uni) ((uint16_t)glyph)
#define set_translate(m, vc) ((unsigned short *)NULL)
#define conv_uni_to_pc(conp, ucs) ((int) (ucs > 0xff ? -1: ucs))
#define conv_8bit_to_uni(c) ((uint32_t)(c))
#define conv_uni_to_8bit(c) ((int) ((c) & 0xff))
#define console_map_init(c) do { ; } while (0)
#endif /* CONFIG_CONSOLE_TRANSLATIONS */

#endif /* __BEEP_CONSOLEMAP_H__ */
