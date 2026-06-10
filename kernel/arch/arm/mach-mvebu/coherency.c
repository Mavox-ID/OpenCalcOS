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
#include <beep/of_address.h>
#include <beep/io.h>
#include <beep/smp.h>
#include <beep/dma-mapping.h>
#include <beep/platform_device.h>
#include <asm/smp_plat.h>
#include "armada-370-xp.h"

/*
 * Some functions in this file are called very early during SMP
 * initialization. At that time the device tree framework is not yet
 * ready, and it is not possible to get the register address to
 * ioremap it. That's why the pointer below is given with an initial
 * value matching its virtual mapping
 */
static void __iomem *coherency_base = ARMADA_370_XP_REGS_VIRT_BASE + 0x20200;
static void __iomem *coherency_cpu_base;

/* Coherency fabric registers */
#define COHERENCY_FABRIC_CFG_OFFSET		   0x4

#define IO_SYNC_BARRIER_CTL_OFFSET		   0x0

static struct of_device_id of_coherency_table[] = {
	{.compatible = "marvell,coherency-fabric"},
	{ /* end of list */ },
};

#ifdef CONFIG_SMP
int coherency_get_cpu_count(void)
{
	int reg, cnt;

	reg = readl(coherency_base + COHERENCY_FABRIC_CFG_OFFSET);
	cnt = (reg & 0xF) + 1;

	return cnt;
}
#endif

/* Function defined in coherency_ll.S */
int ll_set_cpu_coherent(void __iomem *base_addr, unsigned int hw_cpu_id);

int set_cpu_coherent(unsigned int hw_cpu_id, int smp_group_id)
{
	if (!coherency_base) {
		pr_warn("Can't make CPU %d cache coherent.\n", hw_cpu_id);
		pr_warn("Coherency fabric is not initialized\n");
		return 1;
	}

	return ll_set_cpu_coherent(coherency_base, hw_cpu_id);
}

static inline void mvebu_hwcc_sync_io_barrier(void)
{
	writel(0x1, coherency_cpu_base + IO_SYNC_BARRIER_CTL_OFFSET);
	while (readl(coherency_cpu_base + IO_SYNC_BARRIER_CTL_OFFSET) & 0x1);
}

static dma_addr_t mvebu_hwcc_dma_map_page(struct device *dev, struct page *page,
				  unsigned long offset, size_t size,
				  enum dma_data_direction dir,
				  struct dma_attrs *attrs)
{
	if (dir != DMA_TO_DEVICE)
		mvebu_hwcc_sync_io_barrier();
	return pfn_to_dma(dev, page_to_pfn(page)) + offset;
}


static void mvebu_hwcc_dma_unmap_page(struct device *dev, dma_addr_t dma_handle,
			      size_t size, enum dma_data_direction dir,
			      struct dma_attrs *attrs)
{
	if (dir != DMA_TO_DEVICE)
		mvebu_hwcc_sync_io_barrier();
}

static void mvebu_hwcc_dma_sync(struct device *dev, dma_addr_t dma_handle,
			size_t size, enum dma_data_direction dir)
{
	if (dir != DMA_TO_DEVICE)
		mvebu_hwcc_sync_io_barrier();
}

static struct dma_map_ops mvebu_hwcc_dma_ops = {
	.alloc			= arm_dma_alloc,
	.free			= arm_dma_free,
	.mmap			= arm_dma_mmap,
	.map_page		= mvebu_hwcc_dma_map_page,
	.unmap_page		= mvebu_hwcc_dma_unmap_page,
	.get_sgtable		= arm_dma_get_sgtable,
	.map_sg			= arm_dma_map_sg,
	.unmap_sg		= arm_dma_unmap_sg,
	.sync_single_for_cpu	= mvebu_hwcc_dma_sync,
	.sync_single_for_device	= mvebu_hwcc_dma_sync,
	.sync_sg_for_cpu	= arm_dma_sync_sg_for_cpu,
	.sync_sg_for_device	= arm_dma_sync_sg_for_device,
	.set_dma_mask		= arm_dma_set_mask,
};

static int mvebu_hwcc_platform_notifier(struct notifier_block *nb,
				       unsigned long event, void *__dev)
{
	struct device *dev = __dev;

	if (event != BUS_NOTIFY_ADD_DEVICE)
		return NOTIFY_DONE;
	set_dma_ops(dev, &mvebu_hwcc_dma_ops);

	return NOTIFY_OK;
}

static struct notifier_block mvebu_hwcc_platform_nb = {
	.notifier_call = mvebu_hwcc_platform_notifier,
};

int __init coherency_init(void)
{
	struct device_node *np;

	np = of_find_matching_node(NULL, of_coherency_table);
	if (np) {
		pr_info("Initializing Coherency fabric\n");
		coherency_base = of_iomap(np, 0);
		coherency_cpu_base = of_iomap(np, 1);
		set_cpu_coherent(cpu_logical_map(smp_processor_id()), 0);
		bus_register_notifier(&platform_bus_type,
					&mvebu_hwcc_platform_nb);
	}

	return 0;
}
