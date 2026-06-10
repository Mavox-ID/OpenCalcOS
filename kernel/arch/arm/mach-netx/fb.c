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
#include <beep/device.h>
#include <beep/init.h>
#include <beep/dma-mapping.h>
#include <beep/amba/bus.h>
#include <beep/amba/clcd.h>
#include <beep/err.h>
#include <beep/gfp.h>

#include <asm/irq.h>

#include <mach/netx-regs.h>
#include <mach/hardware.h>

static struct clcd_panel *netx_panel;

void netx_clcd_enable(struct clcd_fb *fb)
{
}

int netx_clcd_setup(struct clcd_fb *fb)
{
	dma_addr_t dma;

	fb->panel = netx_panel;

	fb->fb.screen_base = dma_alloc_writecombine(&fb->dev->dev, 1024*1024,
						    &dma, GFP_KERNEL);
	if (!fb->fb.screen_base) {
		printk(KERN_ERR "CLCD: unable to map framebuffer\n");
		return -ENOMEM;
	}

	fb->fb.fix.smem_start	= dma;
	fb->fb.fix.smem_len	= 1024*1024;

	return 0;
}

int netx_clcd_mmap(struct clcd_fb *fb, struct vm_area_struct *vma)
{
	return dma_mmap_writecombine(&fb->dev->dev, vma,
				     fb->fb.screen_base,
				     fb->fb.fix.smem_start,
				     fb->fb.fix.smem_len);
}

void netx_clcd_remove(struct clcd_fb *fb)
{
	dma_free_writecombine(&fb->dev->dev, fb->fb.fix.smem_len,
			      fb->fb.screen_base, fb->fb.fix.smem_start);
}

static AMBA_AHB_DEVICE(fb, "fb", 0, 0x00104000, { NETX_IRQ_LCD }, NULL);

int netx_fb_init(struct clcd_board *board, struct clcd_panel *panel)
{
	netx_panel = panel;
	fb_device.dev.platform_data = board;
	return amba_device_register(&fb_device, &iomem_resource);
}
