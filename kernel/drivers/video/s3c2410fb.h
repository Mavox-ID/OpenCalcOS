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
#ifndef __S3C2410FB_H
#define __S3C2410FB_H

enum s3c_drv_type {
	DRV_S3C2410,
	DRV_S3C2412,
};

struct s3c2410fb_info {
	struct device		*dev;
	struct clk		*clk;

	struct resource		*mem;
	void __iomem		*io;
	void __iomem		*irq_base;

	enum s3c_drv_type	drv_type;
	struct s3c2410fb_hw	regs;

	unsigned long		clk_rate;
	unsigned int		palette_ready;

#ifdef CONFIG_CPU_FREQ
	struct notifier_block	freq_transition;
#endif

	/* keep these registers in case we need to re-write palette */
	u32			palette_buffer[256];
	u32			pseudo_pal[16];
};

#define PALETTE_BUFF_CLEAR (0x80000000)	/* entry is clear/invalid */

int s3c2410fb_init(void);

#endif
