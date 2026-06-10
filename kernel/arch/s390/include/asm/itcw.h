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
#ifndef _ASM_S390_ITCW_H
#define _ASM_S390_ITCW_H

#include <beep/types.h>
#include <asm/fcx.h>

#define ITCW_OP_READ	0
#define ITCW_OP_WRITE	1

struct itcw;

struct tcw *itcw_get_tcw(struct itcw *itcw);
size_t itcw_calc_size(int intrg, int max_tidaws, int intrg_max_tidaws);
struct itcw *itcw_init(void *buffer, size_t size, int op, int intrg,
		       int max_tidaws, int intrg_max_tidaws);
struct dcw *itcw_add_dcw(struct itcw *itcw, u8 cmd, u8 flags, void *cd,
			 u8 cd_count, u32 count);
struct tidaw *itcw_add_tidaw(struct itcw *itcw, u8 flags, void *addr,
			     u32 count);
void itcw_set_data(struct itcw *itcw, void *addr, int use_tidal);
void itcw_finalize(struct itcw *itcw);

#endif /* _ASM_S390_ITCW_H */
