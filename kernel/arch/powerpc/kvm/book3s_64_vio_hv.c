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
#include <beep/types.h>
#include <beep/string.h>
#include <beep/kvm.h>
#include <beep/kvm_host.h>
#include <beep/highmem.h>
#include <beep/gfp.h>
#include <beep/slab.h>
#include <beep/hugetlb.h>
#include <beep/list.h>

#include <asm/tlbflush.h>
#include <asm/kvm_ppc.h>
#include <asm/kvm_book3s.h>
#include <asm/mmu-hash64.h>
#include <asm/hvcall.h>
#include <asm/synch.h>
#include <asm/ppc-opcode.h>
#include <asm/kvm_host.h>
#include <asm/udbg.h>

#define TCES_PER_PAGE	(PAGE_SIZE / sizeof(u64))

/* WARNING: This will be called in real-mode on HV KVM and virtual
 *          mode on PR KVM
 */
long kvmppc_h_put_tce(struct kvm_vcpu *vcpu, unsigned long liobn,
		      unsigned long ioba, unsigned long tce)
{
	struct kvm *kvm = vcpu->kvm;
	struct kvmppc_spapr_tce_table *stt;

	/* udbg_printf("H_PUT_TCE(): liobn=0x%lx ioba=0x%lx, tce=0x%lx\n", */
	/* 	    liobn, ioba, tce); */

	list_for_each_entry(stt, &kvm->arch.spapr_tce_tables, list) {
		if (stt->liobn == liobn) {
			unsigned long idx = ioba >> SPAPR_TCE_SHIFT;
			struct page *page;
			u64 *tbl;

			/* udbg_printf("H_PUT_TCE: liobn 0x%lx => stt=%p  window_size=0x%x\n", */
			/* 	    liobn, stt, stt->window_size); */
			if (ioba >= stt->window_size)
				return H_PARAMETER;

			page = stt->pages[idx / TCES_PER_PAGE];
			tbl = (u64 *)page_address(page);

			/* FIXME: Need to validate the TCE itself */
			/* udbg_printf("tce @ %p\n", &tbl[idx % TCES_PER_PAGE]); */
			tbl[idx % TCES_PER_PAGE] = tce;
			return H_SUCCESS;
		}
	}

	/* Didn't find the liobn, punt it to userspace */
	return H_TOO_HARD;
}
