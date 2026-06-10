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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/mm.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/memblock.h>
#include <beep/io.h>
#include <beep/omapfb.h>
#include <beep/dma-mapping.h>

#include <asm/mach/map.h>

#if defined(CONFIG_FB_OMAP) || defined(CONFIG_FB_OMAP_MODULE)

static bool omapfb_lcd_configured;
static struct omapfb_platform_data omapfb_config;

static u64 omap_fb_dma_mask = ~(u32)0;

static struct platform_device omap_fb_device = {
	.name		= "omapfb",
	.id		= -1,
	.dev = {
		.dma_mask		= &omap_fb_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &omapfb_config,
	},
	.num_resources = 0,
};

void __init omapfb_set_lcd_config(const struct omap_lcd_config *config)
{
	omapfb_config.lcd = *config;
	omapfb_lcd_configured = true;
}

static int __init omap_init_fb(void)
{
	/*
	 * If the board file has not set the lcd config with
	 * omapfb_set_lcd_config(), don't bother registering the omapfb device
	 */
	if (!omapfb_lcd_configured)
		return 0;

	return platform_device_register(&omap_fb_device);
}

arch_initcall(omap_init_fb);

#else

void __init omapfb_set_lcd_config(const struct omap_lcd_config *config)
{
}

#endif
