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
#include <beep/mm.h>
#include <beep/bootmem.h>
#include <beep/list.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/sun3mmu.h>
#include <asm/dvma.h>


static unsigned long ptelist[120];

static unsigned long dvma_page(unsigned long kaddr, unsigned long vaddr)
{
	unsigned long pte;
	unsigned long j;
	pte_t ptep;

	j = *(volatile unsigned long *)kaddr;
	*(volatile unsigned long *)kaddr = j;

	ptep = pfn_pte(virt_to_pfn(kaddr), PAGE_KERNEL);
	pte = pte_val(ptep);
//		printk("dvma_remap: addr %lx -> %lx pte %08lx len %x\n",
//		       kaddr, vaddr, pte, len);
	if(ptelist[(vaddr & 0xff000) >> PAGE_SHIFT] != pte) {
		sun3_put_pte(vaddr, pte);
		ptelist[(vaddr & 0xff000) >> PAGE_SHIFT] = pte;
	}

	return (vaddr + (kaddr & ~PAGE_MASK));

}

int dvma_map_iommu(unsigned long kaddr, unsigned long baddr,
			      int len)
{

	unsigned long end;
	unsigned long vaddr;

	vaddr = dvma_btov(baddr);

	end = vaddr + len;

	while(vaddr < end) {
		dvma_page(kaddr, vaddr);
		kaddr += PAGE_SIZE;
		vaddr += PAGE_SIZE;
	}

	return 0;

}

void sun3_dvma_init(void)
{

	memset(ptelist, 0, sizeof(ptelist));


}
