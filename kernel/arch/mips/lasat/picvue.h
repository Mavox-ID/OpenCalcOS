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
struct pvc_defs {
	volatile u32 *reg;
	u32 data_shift;
	u32 data_mask;
	u32 e;
	u32 rw;
	u32 rs;
};

extern struct pvc_defs *picvue;

#define PVC_NLINES		2
#define PVC_DISPMEM		80
#define PVC_LINELEN		PVC_DISPMEM / PVC_NLINES
#define PVC_VISIBLE_CHARS	16

void pvc_write_string(const unsigned char *str, u8 addr, int line);
void pvc_write_string_centered(const unsigned char *str, int line);
void pvc_dump_string(const unsigned char *str);

#define BM_SIZE			8
#define MAX_PROGRAMMABLE_CHARS	8
int pvc_program_cg(int charnum, u8 bitmap[BM_SIZE]);

void pvc_dispcnt(u8 cmd);
#define  DISP_OFF	0
#define  DISP_ON	(1 << 2)
#define  CUR_ON		(1 << 1)
#define  CUR_BLINK	(1 << 0)

void pvc_move(u8 cmd);
#define  DISPLAY	(1 << 3)
#define  CURSOR		0
#define  RIGHT		(1 << 2)
#define  LEFT		0

void pvc_clear(void);
void pvc_home(void);
