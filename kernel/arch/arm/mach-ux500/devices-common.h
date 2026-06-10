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
#ifndef __DEVICES_COMMON_H
#define __DEVICES_COMMON_H

#include <beep/platform_device.h>
#include <beep/dma-mapping.h>
#include <beep/sys_soc.h>
#include <beep/amba/bus.h>
#include <beep/platform_data/i2c-nomadik.h>
#include <beep/platform_data/crypto-ux500.h>

struct spi_master_cntlr;

static inline struct amba_device *
dbx500_add_msp_spi(struct device *parent, const char *name,
		   resource_size_t base, int irq,
		   struct spi_master_cntlr *pdata)
{
	return amba_ahb_device_add(parent, name, base, SZ_4K, irq, 0,
				   pdata, 0);
}

static inline struct amba_device *
dbx500_add_spi(struct device *parent, const char *name, resource_size_t base,
	       int irq, struct spi_master_cntlr *pdata,
	       u32 periphid)
{
	return amba_ahb_device_add(parent, name, base, SZ_4K, irq, 0,
				   pdata, periphid);
}

struct mmci_platform_data;

static inline struct amba_device *
dbx500_add_sdi(struct device *parent, const char *name, resource_size_t base,
	       int irq, struct mmci_platform_data *pdata, u32 periphid)
{
	return amba_ahb_device_add(parent, name, base, SZ_4K, irq, 0,
				   pdata, periphid);
}

struct amba_pl011_data;

static inline struct amba_device *
dbx500_add_uart(struct device *parent, const char *name, resource_size_t base,
		int irq, struct amba_pl011_data *pdata)
{
	return amba_ahb_device_add(parent, name, base, SZ_4K, irq, 0, pdata, 0);
}

struct nmk_i2c_controller;

static inline struct amba_device *
dbx500_add_i2c(struct device *parent, int id, resource_size_t base, int irq,
	       struct nmk_i2c_controller *data)
{
	/* Conjure a name similar to what the platform device used to have */
	char name[16];

	snprintf(name, sizeof(name), "nmk-i2c.%d", id);
	return amba_apb_device_add(parent, name, base, SZ_4K, irq, 0, data, 0);
}

static inline struct amba_device *
dbx500_add_rtc(struct device *parent, resource_size_t base, int irq)
{
	return amba_apb_device_add(parent, "rtc-pl031", base, SZ_4K, irq,
				0, NULL, 0);
}

struct cryp_platform_data;

static inline struct platform_device *
dbx500_add_cryp1(struct device *parent, int id, resource_size_t base, int irq,
		struct cryp_platform_data *pdata)
{
	struct resource res[] = {
			DEFINE_RES_MEM(base, SZ_4K),
			DEFINE_RES_IRQ(irq),
	};

	struct platform_device_info pdevinfo = {
			.parent = parent,
			.name = "cryp1",
			.id = id,
			.res = res,
			.num_res = ARRAY_SIZE(res),
			.data = pdata,
			.size_data = sizeof(*pdata),
			.dma_mask = DMA_BIT_MASK(32),
	};

	return platform_device_register_full(&pdevinfo);
}

struct hash_platform_data;

static inline struct platform_device *
dbx500_add_hash1(struct device *parent, int id, resource_size_t base,
		struct hash_platform_data *pdata)
{
	struct resource res[] = {
			DEFINE_RES_MEM(base, SZ_4K),
	};

	struct platform_device_info pdevinfo = {
			.parent = parent,
			.name = "hash1",
			.id = id,
			.res = res,
			.num_res = ARRAY_SIZE(res),
			.data = pdata,
			.size_data = sizeof(*pdata),
			.dma_mask = DMA_BIT_MASK(32),
	};

	return platform_device_register_full(&pdevinfo);
}

struct nmk_gpio_platform_data;

void dbx500_add_gpios(struct device *parent, resource_size_t *base, int num,
		      int irq, struct nmk_gpio_platform_data *pdata);

static inline void
dbx500_add_pinctrl(struct device *parent, const char *name,
		   resource_size_t base)
{
	struct resource res[] = {
		DEFINE_RES_MEM(base, SZ_8K),
	};
	struct platform_device_info pdevinfo = {
		.parent = parent,
		.name = name,
		.id = -1,
		.res = res,
		.num_res = ARRAY_SIZE(res),
	};

	platform_device_register_full(&pdevinfo);
}

#endif
