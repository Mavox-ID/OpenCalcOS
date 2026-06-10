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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/gfp.h>
#include <beep/module.h>
#include <beep/elf.h>
#include <beep/sched.h>
#include <beep/err.h>

/*
 * Should the kernel map a VDSO page into processes and pass its
 * address down to glibc upon exec()?
 */
unsigned int __read_mostly vdso_enabled = 1;
EXPORT_SYMBOL_GPL(vdso_enabled);

static int __init vdso_setup(char *s)
{
	vdso_enabled = simple_strtoul(s, NULL, 0);
	return 1;
}
__setup("vdso=", vdso_setup);

/*
 * These symbols are defined by vsyscall.o to mark the bounds
 * of the ELF DSO images included therein.
 */
extern const char vsyscall_trapa_start, vsyscall_trapa_end;
static struct page *syscall_pages[1];

int __init vsyscall_init(void)
{
	void *syscall_page = (void *)get_zeroed_page(GFP_ATOMIC);
	syscall_pages[0] = virt_to_page(syscall_page);

	/*
	 * XXX: Map this page to a fixmap entry if we get around
	 * to adding the page to ELF core dumps
	 */

	memcpy(syscall_page,
	       &vsyscall_trapa_start,
	       &vsyscall_trapa_end - &vsyscall_trapa_start);

	return 0;
}

/* Setup a VMA at program startup for the vsyscall page */
int arch_setup_additional_pages(struct beep_binprm *bprm, int uses_interp)
{
	struct mm_struct *mm = current->mm;
	unsigned long addr;
	int ret;

	down_write(&mm->mmap_sem);
	addr = get_unmapped_area(NULL, 0, PAGE_SIZE, 0, 0);
	if (IS_ERR_VALUE(addr)) {
		ret = addr;
		goto up_fail;
	}

	ret = install_special_mapping(mm, addr, PAGE_SIZE,
				      VM_READ | VM_EXEC |
				      VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC,
				      syscall_pages);
	if (unlikely(ret))
		goto up_fail;

	current->mm->context.vdso = (void *)addr;

up_fail:
	up_write(&mm->mmap_sem);
	return ret;
}

const char *arch_vma_name(struct vm_area_struct *vma)
{
	if (vma->vm_mm && vma->vm_start == (long)vma->vm_mm->context.vdso)
		return "[vdso]";

	return NULL;
}

struct vm_area_struct *get_gate_vma(struct mm_struct *mm)
{
	return NULL;
}

int in_gate_area(struct mm_struct *mm, unsigned long address)
{
	return 0;
}

int in_gate_area_no_mm(unsigned long address)
{
	return 0;
}
