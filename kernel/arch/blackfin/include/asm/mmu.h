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
#ifndef __MMU_H
#define __MMU_H

struct sram_list_struct {
	struct sram_list_struct *next;
	void *addr;
	size_t length;
};

typedef struct {
	unsigned long end_brk;
	unsigned long stack_start;

	/* Points to the location in SDRAM where the L1 stack is normally
	   saved, or NULL if the stack is always in SDRAM.  */
	void *l1_stack_save;

	struct sram_list_struct *sram_list;

#ifdef CONFIG_BINFMT_ELF_FDPIC
	unsigned long	exec_fdpic_loadmap;
	unsigned long	interp_fdpic_loadmap;
#endif
#ifdef CONFIG_MPU
	unsigned long *page_rwx_mask;
#endif
} mm_context_t;

#endif
