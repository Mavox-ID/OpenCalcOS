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
#include <beep/usb.h>
#include <beep/io.h>
#include <beep/usb/otg.h>
#include <beep/usb/ulpi.h>

#define ULPI_VIEW_WAKEUP	(1 << 31)
#define ULPI_VIEW_RUN		(1 << 30)
#define ULPI_VIEW_WRITE		(1 << 29)
#define ULPI_VIEW_READ		(0 << 29)
#define ULPI_VIEW_ADDR(x)	(((x) & 0xff) << 16)
#define ULPI_VIEW_DATA_READ(x)	(((x) >> 8) & 0xff)
#define ULPI_VIEW_DATA_WRITE(x)	((x) & 0xff)

static int ulpi_viewport_wait(void __iomem *view, u32 mask)
{
	unsigned long usec = 2000;

	while (usec--) {
		if (!(readl(view) & mask))
			return 0;

		udelay(1);
	};

	return -ETIMEDOUT;
}

static int ulpi_viewport_read(struct usb_phy *otg, u32 reg)
{
	int ret;
	void __iomem *view = otg->io_priv;

	writel(ULPI_VIEW_WAKEUP | ULPI_VIEW_WRITE, view);
	ret = ulpi_viewport_wait(view, ULPI_VIEW_WAKEUP);
	if (ret)
		return ret;

	writel(ULPI_VIEW_RUN | ULPI_VIEW_READ | ULPI_VIEW_ADDR(reg), view);
	ret = ulpi_viewport_wait(view, ULPI_VIEW_RUN);
	if (ret)
		return ret;

	return ULPI_VIEW_DATA_READ(readl(view));
}

static int ulpi_viewport_write(struct usb_phy *otg, u32 val, u32 reg)
{
	int ret;
	void __iomem *view = otg->io_priv;

	writel(ULPI_VIEW_WAKEUP | ULPI_VIEW_WRITE, view);
	ret = ulpi_viewport_wait(view, ULPI_VIEW_WAKEUP);
	if (ret)
		return ret;

	writel(ULPI_VIEW_RUN | ULPI_VIEW_WRITE | ULPI_VIEW_DATA_WRITE(val) |
						 ULPI_VIEW_ADDR(reg), view);

	return ulpi_viewport_wait(view, ULPI_VIEW_RUN);
}

struct usb_phy_io_ops ulpi_viewport_access_ops = {
	.read	= ulpi_viewport_read,
	.write	= ulpi_viewport_write,
};
