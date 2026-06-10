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
#ifndef ASMARM_DEVICE_H
#define ASMARM_DEVICE_H

struct dev_archdata {
	struct dma_map_ops	*dma_ops;
#ifdef CONFIG_DMABOUNCE
	struct dmabounce_device_info *dmabounce;
#endif
#ifdef CONFIG_IOMMU_API
	void *iommu; /* private IOMMU data */
#endif
#ifdef CONFIG_ARM_DMA_USE_IOMMU
	struct dma_iommu_mapping	*mapping;
#endif
};

struct omap_device;

struct pdev_archdata {
#ifdef CONFIG_ARCH_OMAP
	struct omap_device *od;
#endif
};

#endif
