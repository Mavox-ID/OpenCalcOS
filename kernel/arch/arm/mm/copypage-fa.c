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
#include <beep/init.h>
#include <beep/highmem.h>

/*
 * Faraday optimised copy_user_page
 */
static void __naked
fa_copy_user_page(void *kto, const void *kfrom)
{
	asm("\
	stmfd	sp!, {r4, lr}			@ 2\n\
	mov	r2, %0				@ 1\n\
1:	ldmia	r1!, {r3, r4, ip, lr}		@ 4\n\
	stmia	r0, {r3, r4, ip, lr}		@ 4\n\
	mcr	p15, 0, r0, c7, c14, 1		@ 1   clean and invalidate D line\n\
	add	r0, r0, #16			@ 1\n\
	ldmia	r1!, {r3, r4, ip, lr}		@ 4\n\
	stmia	r0, {r3, r4, ip, lr}		@ 4\n\
	mcr	p15, 0, r0, c7, c14, 1		@ 1   clean and invalidate D line\n\
	add	r0, r0, #16			@ 1\n\
	subs	r2, r2, #1			@ 1\n\
	bne	1b				@ 1\n\
	mcr	p15, 0, r2, c7, c10, 4		@ 1   drain WB\n\
	ldmfd	sp!, {r4, pc}			@ 3"
	:
	: "I" (PAGE_SIZE / 32));
}

void fa_copy_user_highpage(struct page *to, struct page *from,
	unsigned long vaddr, struct vm_area_struct *vma)
{
	void *kto, *kfrom;

	kto = kmap_atomic(to);
	kfrom = kmap_atomic(from);
	fa_copy_user_page(kto, kfrom);
	kunmap_atomic(kfrom);
	kunmap_atomic(kto);
}

/*
 * Faraday optimised clear_user_page
 *
 * Same story as above.
 */
void fa_clear_user_highpage(struct page *page, unsigned long vaddr)
{
	void *ptr, *kaddr = kmap_atomic(page);
	asm volatile("\
	mov	r1, %2				@ 1\n\
	mov	r2, #0				@ 1\n\
	mov	r3, #0				@ 1\n\
	mov	ip, #0				@ 1\n\
	mov	lr, #0				@ 1\n\
1:	stmia	%0, {r2, r3, ip, lr}		@ 4\n\
	mcr	p15, 0, %0, c7, c14, 1		@ 1   clean and invalidate D line\n\
	add	%0, %0, #16			@ 1\n\
	stmia	%0, {r2, r3, ip, lr}		@ 4\n\
	mcr	p15, 0, %0, c7, c14, 1		@ 1   clean and invalidate D line\n\
	add	%0, %0, #16			@ 1\n\
	subs	r1, r1, #1			@ 1\n\
	bne	1b				@ 1\n\
	mcr	p15, 0, r1, c7, c10, 4		@ 1   drain WB"
	: "=r" (ptr)
	: "0" (kaddr), "I" (PAGE_SIZE / 32)
	: "r1", "r2", "r3", "ip", "lr");
	kunmap_atomic(kaddr);
}

struct cpu_user_fns fa_user_fns __initdata = {
	.cpu_clear_user_highpage = fa_clear_user_highpage,
	.cpu_copy_user_highpage	= fa_copy_user_highpage,
};
