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
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/ioport.h>
#include <beep/efi.h>

#include <asm/io.h>
#include <asm/desc.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/tlbflush.h>
#include <asm/efi.h>

/*
 * To make EFI call EFI runtime service in physical addressing mode we need
 * prelog/epilog before/after the invocation to disable interrupt, to
 * claim EFI runtime service handler exclusively and to duplicate a memory in
 * low memory space say 0 - 3G.
 */

static unsigned long efi_rt_eflags;

void efi_call_phys_prelog(void)
{
	struct desc_ptr gdt_descr;

	local_irq_save(efi_rt_eflags);

	load_cr3(initial_page_table);
	__flush_tlb_all();

	gdt_descr.address = __pa(get_cpu_gdt_table(0));
	gdt_descr.size = GDT_SIZE - 1;
	load_gdt(&gdt_descr);
}

void efi_call_phys_epilog(void)
{
	struct desc_ptr gdt_descr;

	gdt_descr.address = (unsigned long)get_cpu_gdt_table(0);
	gdt_descr.size = GDT_SIZE - 1;
	load_gdt(&gdt_descr);

	load_cr3(swapper_pg_dir);
	__flush_tlb_all();

	local_irq_restore(efi_rt_eflags);
}
