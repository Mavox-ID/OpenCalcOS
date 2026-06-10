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
#ifndef _DRM_INTEL_GTT_H
#define	_DRM_INTEL_GTT_H

struct intel_gtt {
	/* Size of memory reserved for graphics by the BIOS */
	unsigned int stolen_size;
	/* Total number of gtt entries. */
	unsigned int gtt_total_entries;
	/* Part of the gtt that is mappable by the cpu, for those chips where
	 * this is not the full gtt. */
	unsigned int gtt_mappable_entries;
	/* Whether i915 needs to use the dmar apis or not. */
	unsigned int needs_dmar : 1;
	/* Whether we idle the gpu before mapping/unmapping */
	unsigned int do_idle_maps : 1;
	/* Share the scratch page dma with ppgtts. */
	dma_addr_t scratch_page_dma;
	struct page *scratch_page;
	/* for ppgtt PDE access */
	u32 __iomem *gtt;
	/* needed for ioremap in drm/i915 */
	phys_addr_t gma_bus_addr;
} *intel_gtt_get(void);

int intel_gmch_probe(struct pci_dev *bridge_pdev, struct pci_dev *gpu_pdev,
		     struct agp_bridge_data *bridge);
void intel_gmch_remove(void);

bool intel_enable_gtt(void);

void intel_gtt_chipset_flush(void);
void intel_gtt_insert_sg_entries(struct sg_table *st,
				 unsigned int pg_start,
				 unsigned int flags);
void intel_gtt_clear_range(unsigned int first_entry, unsigned int num_entries);

/* Special gtt memory types */
#define AGP_DCACHE_MEMORY	1
#define AGP_PHYS_MEMORY		2

/* flag for GFDT type */
#define AGP_USER_CACHED_MEMORY_GFDT (1 << 3)

#ifdef CONFIG_INTEL_IOMMU
extern int intel_iommu_gfx_mapped;
#endif

#endif
