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
/* Copyright 2002,2003 by Andi Kleen, SuSE Labs */
/* 2.5 Version loosely based on the NUMAQ Code by Pat Gaughen. */
#ifndef _ASM_X86_MMZONE_64_H
#define _ASM_X86_MMZONE_64_H

#ifdef CONFIG_NUMA

#include <beep/mmdebug.h>
#include <asm/smp.h>

extern struct pglist_data *node_data[];

#define NODE_DATA(nid)		(node_data[nid])

#endif
#endif /* _ASM_X86_MMZONE_64_H */
