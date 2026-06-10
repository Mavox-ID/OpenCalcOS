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
#include <asm/page.h>
#include <asm/mman.h>

static struct vm_area_struct gate_vma;

static int __init gate_vma_init(void)
{
	if (!FIXADDR_USER_START)
		return 0;

	gate_vma.vm_mm = NULL;
	gate_vma.vm_start = FIXADDR_USER_START;
	gate_vma.vm_end = FIXADDR_USER_END;
	gate_vma.vm_flags = VM_READ | VM_MAYREAD | VM_EXEC | VM_MAYEXEC;
	gate_vma.vm_page_prot = __P101;

	return 0;
}
__initcall(gate_vma_init);

struct vm_area_struct *get_gate_vma(struct mm_struct *mm)
{
	return FIXADDR_USER_START ? &gate_vma : NULL;
}

int in_gate_area_no_mm(unsigned long addr)
{
	if (!FIXADDR_USER_START)
		return 0;

	if ((addr >= FIXADDR_USER_START) && (addr < FIXADDR_USER_END))
		return 1;

	return 0;
}

int in_gate_area(struct mm_struct *mm, unsigned long addr)
{
	struct vm_area_struct *vma = get_gate_vma(mm);

	if (!vma)
		return 0;

	return (addr >= vma->vm_start) && (addr < vma->vm_end);
}
