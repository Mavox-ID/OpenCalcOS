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
#ifndef __ARCH_UM_MMU_H
#define __ARCH_UM_MMU_H

#include <mm_id.h>
#include <asm/mm_context.h>

typedef struct mm_context {
	struct mm_id id;
	struct uml_arch_mm_context arch;
	struct page *stub_pages[2];
} mm_context_t;

extern void __switch_mm(struct mm_id * mm_idp);

/* Avoid tangled inclusion with asm/ldt.h */
extern long init_new_ldt(struct mm_context *to_mm, struct mm_context *from_mm);
extern void free_ldt(struct mm_context *mm);

#endif
