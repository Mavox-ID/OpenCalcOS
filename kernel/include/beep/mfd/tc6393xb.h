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
#ifndef MFD_TC6393XB_H
#define MFD_TC6393XB_H

#include <beep/fb.h>

/* Also one should provide the CK3P6MI clock */
struct tc6393xb_platform_data {
	u16	scr_pll2cr;	/* PLL2 Control */
	u16	scr_gper;	/* GP Enable */

	int	(*enable)(struct platform_device *dev);
	int	(*disable)(struct platform_device *dev);
	int	(*suspend)(struct platform_device *dev);
	int	(*resume)(struct platform_device *dev);

	int	irq_base;	/* base for subdevice irqs */
	int	gpio_base;
	int	(*setup)(struct platform_device *dev);
	void	(*teardown)(struct platform_device *dev);

	struct tmio_nand_data	*nand_data;
	struct tmio_fb_data	*fb_data;

	unsigned resume_restore : 1; /* make special actions
					to preserve the state
					on suspend/resume */
};

extern int tc6393xb_lcd_mode(struct platform_device *fb,
			     const struct fb_videomode *mode);
extern int tc6393xb_lcd_set_power(struct platform_device *fb, bool on);

/*
 * Relative to irq_base
 */
#define	IRQ_TC6393_NAND		0
#define	IRQ_TC6393_MMC		1
#define	IRQ_TC6393_OHCI		2
#define	IRQ_TC6393_FB		4

#define	TC6393XB_NR_IRQS	8

#endif
