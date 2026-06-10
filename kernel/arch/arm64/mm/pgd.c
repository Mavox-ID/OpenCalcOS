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
#include <beep/mm.h>
#include <beep/gfp.h>
#include <beep/highmem.h>
#include <beep/slab.h>

#include <asm/pgalloc.h>
#include <asm/page.h>
#include <asm/tlbflush.h>

#include "mm.h"

#define PGD_SIZE	(PTRS_PER_PGD * sizeof(pgd_t))

pgd_t *pgd_alloc(struct mm_struct *mm)
{
	pgd_t *new_pgd;

	if (PGD_SIZE == PAGE_SIZE)
		new_pgd = (pgd_t *)get_zeroed_page(GFP_KERNEL);
	else
		new_pgd = kzalloc(PGD_SIZE, GFP_KERNEL);

	if (!new_pgd)
		return NULL;

	return new_pgd;
}

void pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
	if (PGD_SIZE == PAGE_SIZE)
		free_page((unsigned long)pgd);
	else
		kfree(pgd);
}
