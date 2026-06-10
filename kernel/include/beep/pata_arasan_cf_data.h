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
#ifndef _PATA_ARASAN_CF_DATA_H
#define _PATA_ARASAN_CF_DATA_H

#include <beep/platform_device.h>

struct arasan_cf_pdata {
	u8 cf_if_clk;
	#define CF_IF_CLK_100M			(0x0)
	#define CF_IF_CLK_75M			(0x1)
	#define CF_IF_CLK_66M			(0x2)
	#define CF_IF_CLK_50M			(0x3)
	#define CF_IF_CLK_40M			(0x4)
	#define CF_IF_CLK_33M			(0x5)
	#define CF_IF_CLK_25M			(0x6)
	#define CF_IF_CLK_125M			(0x7)
	#define CF_IF_CLK_150M			(0x8)
	#define CF_IF_CLK_166M			(0x9)
	#define CF_IF_CLK_200M			(0xA)
	/*
	 * Platform specific incapabilities of CF controller is handled via
	 * quirks
	 */
	u32 quirk;
	#define CF_BROKEN_PIO			(1)
	#define CF_BROKEN_MWDMA			(1 << 1)
	#define CF_BROKEN_UDMA			(1 << 2)
	/* This is platform specific data for the DMA controller */
	void *dma_priv;
};

static inline void
set_arasan_cf_pdata(struct platform_device *pdev, struct arasan_cf_pdata *data)
{
	pdev->dev.platform_data = data;
}
#endif /* _PATA_ARASAN_CF_DATA_H */
