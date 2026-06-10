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
#include <beep/mmzone.h>
#include <beep/module.h>
#include <beep/io.h>
#include <gxio/iorpc_globals.h>
#include <gxio/kiorpc.h>

#ifdef DEBUG_IORPC
#define TRACE(FMT, ...) pr_info(SIMPLE_MSG_LINE FMT, ## __VA_ARGS__)
#else
#define TRACE(...)
#endif

/* Create kernel-VA-space MMIO mapping for an on-chip IO device. */
void __iomem *iorpc_ioremap(int hv_fd, resource_size_t offset,
			    unsigned long size)
{
	pgprot_t mmio_base, prot = { 0 };
	unsigned long pfn;
	int err;

	/* Look up the shim's lotar and base PA. */
	err = __iorpc_get_mmio_base(hv_fd, &mmio_base);
	if (err) {
		TRACE("get_mmio_base() failure: %d\n", err);
		return NULL;
	}

	/* Make sure the HV driver approves of our offset and size. */
	err = __iorpc_check_mmio_offset(hv_fd, offset, size);
	if (err) {
		TRACE("check_mmio_offset() failure: %d\n", err);
		return NULL;
	}

	/*
	 * mmio_base contains a base pfn and homing coordinates.  Turn
	 * it into an MMIO pgprot and offset pfn.
	 */
	prot = hv_pte_set_lotar(prot, hv_pte_get_lotar(mmio_base));
	pfn = pte_pfn(mmio_base) + PFN_DOWN(offset);

	return ioremap_prot(PFN_PHYS(pfn), size, prot);
}

EXPORT_SYMBOL(iorpc_ioremap);
