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
#ifndef __ASM_SN_FRU_H
#define __ASM_SN_FRU_H

#define MAX_DIMMS			8	 /* max # of dimm banks */
#define MAX_PCIDEV			8	 /* max # of pci devices on a pci bus */

typedef unsigned char confidence_t;

typedef struct kf_mem_s {
	confidence_t km_confidence; /* confidence level that the memory is bad
				     * is this necessary ?
				     */
	confidence_t km_dimm[MAX_DIMMS];
	                            /* confidence level that dimm[i] is bad
				     *I think this is the right number
				     */

} kf_mem_t;

typedef struct kf_cpu_s {
	confidence_t  	kc_confidence; /* confidence level that cpu is bad */
	confidence_t  	kc_icache; /* confidence level that instr. cache is bad */
	confidence_t  	kc_dcache; /* confidence level that data   cache is bad */
	confidence_t  	kc_scache; /* confidence level that sec.   cache is bad */
	confidence_t	kc_sysbus; /* confidence level that sysad/cmd/state bus is bad */
} kf_cpu_t;

typedef struct kf_pci_bus_s {
	confidence_t	kpb_belief;	/* confidence level  that the  pci bus is bad */
	confidence_t	kpb_pcidev_belief[MAX_PCIDEV];
	                                /* confidence level that the pci dev is bad */
} kf_pci_bus_t;

#endif /* __ASM_SN_FRU_H */
