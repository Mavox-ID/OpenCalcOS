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
#include <beep/init.h>
#include <beep/mm.h>
#include <beep/types.h>
#include <beep/spinlock.h>
#include <beep/bootmem.h>
#include <beep/ioport.h>
#include <beep/module.h>
#include <beep/efi.h>
#include <beep/uaccess.h>
#include <beep/io.h>
#include <beep/reboot.h>

#include <asm/setup.h>
#include <asm/page.h>
#include <asm/e820.h>
#include <asm/pgtable.h>
#include <asm/tlbflush.h>
#include <asm/proto.h>
#include <asm/efi.h>
#include <asm/cacheflush.h>
#include <asm/fixmap.h>

static pgd_t save_pgd __initdata;
static unsigned long efi_flags __initdata;

static void __init early_code_mapping_set_exec(int executable)
{
	efi_memory_desc_t *md;
	void *p;

	if (!(__supported_pte_mask & _PAGE_NX))
		return;

	/* Make EFI service code area executable */
	for (p = memmap.map; p < memmap.map_end; p += memmap.desc_size) {
		md = p;
		if (md->type == EFI_RUNTIME_SERVICES_CODE ||
		    md->type == EFI_BOOT_SERVICES_CODE)
			efi_set_executable(md, executable);
	}
}

void __init efi_call_phys_prelog(void)
{
	unsigned long vaddress;

	early_code_mapping_set_exec(1);
	local_irq_save(efi_flags);
	vaddress = (unsigned long)__va(0x0UL);
	save_pgd = *pgd_offset_k(0x0UL);
	set_pgd(pgd_offset_k(0x0UL), *pgd_offset_k(vaddress));
	__flush_tlb_all();
}

void __init efi_call_phys_epilog(void)
{
	/*
	 * After the lock is released, the original page table is restored.
	 */
	set_pgd(pgd_offset_k(0x0UL), save_pgd);
	__flush_tlb_all();
	local_irq_restore(efi_flags);
	early_code_mapping_set_exec(0);
}

void __iomem *__init efi_ioremap(unsigned long phys_addr, unsigned long size,
				 u32 type, u64 attribute)
{
	unsigned long last_map_pfn;

	if (type == EFI_MEMORY_MAPPED_IO)
		return ioremap(phys_addr, size);

	last_map_pfn = init_memory_mapping(phys_addr, phys_addr + size);
	if ((last_map_pfn << PAGE_SHIFT) < phys_addr + size) {
		unsigned long top = last_map_pfn << PAGE_SHIFT;
		efi_ioremap(top, size - (top - phys_addr), type, attribute);
	}

	if (!(attribute & EFI_MEMORY_WB))
		efi_memory_uc((u64)(unsigned long)__va(phys_addr), size);

	return (void __iomem *)__va(phys_addr);
}
