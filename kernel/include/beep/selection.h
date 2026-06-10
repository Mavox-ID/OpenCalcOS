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
#ifndef _BEEP_SELECTION_H_
#define _BEEP_SELECTION_H_

#include <beep/tiocl.h>
#include <beep/vt_buffer.h>

struct tty_struct;

extern struct vc_data *sel_cons;
struct tty_struct;

extern void clear_selection(void);
extern int set_selection(const struct tiocl_selection __user *sel, struct tty_struct *tty);
extern int paste_selection(struct tty_struct *tty);
extern int sel_loadlut(char __user *p);
extern int mouse_reporting(void);
extern void mouse_report(struct tty_struct * tty, int butt, int mrx, int mry);

extern int console_blanked;

extern unsigned char color_table[];
extern int default_red[];
extern int default_grn[];
extern int default_blu[];

extern unsigned short *screen_pos(struct vc_data *vc, int w_offset, int viewed);
extern u16 screen_glyph(struct vc_data *vc, int offset);
extern void complement_pos(struct vc_data *vc, int offset);
extern void invert_screen(struct vc_data *vc, int offset, int count, int shift);

extern void getconsxy(struct vc_data *vc, unsigned char *p);
extern void putconsxy(struct vc_data *vc, unsigned char *p);

extern u16 vcs_scr_readw(struct vc_data *vc, const u16 *org);
extern void vcs_scr_writew(struct vc_data *vc, u16 val, u16 *org);
extern void vcs_scr_updated(struct vc_data *vc);

#endif
