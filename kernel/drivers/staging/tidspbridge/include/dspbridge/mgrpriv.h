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
#ifndef MGRPRIV_
#define MGRPRIV_

/*
 * OMAP1510 specific
 */
#define MGR_MAXTLBENTRIES  32

/* RM MGR Object */
struct mgr_object;

struct mgr_tlbentry {
	u32 dsp_virt;	/* DSP virtual address */
	u32 gpp_phys;	/* GPP physical address */
};

/*
 *  The DSP_PROCESSOREXTINFO structure describes additional extended
 *  capabilities of a DSP processor not exposed to user.
 */
struct mgr_processorextinfo {
	struct dsp_processorinfo ty_basic;	/* user processor info */
	/* private dsp mmu entries */
	struct mgr_tlbentry ty_tlb[MGR_MAXTLBENTRIES];
};

#endif /* MGRPRIV_ */
