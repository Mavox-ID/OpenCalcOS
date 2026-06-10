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
#ifndef __MUSB_BEEP_PLATFORM_ARCH_H__
#define __MUSB_BEEP_PLATFORM_ARCH_H__

#include <beep/io.h>

#ifndef CONFIG_BLACKFIN

/* NOTE:  these offsets are all in bytes */

static inline u16 musb_readw(const void __iomem *addr, unsigned offset)
	{ return __raw_readw(addr + offset); }

static inline u32 musb_readl(const void __iomem *addr, unsigned offset)
	{ return __raw_readl(addr + offset); }


static inline void musb_writew(void __iomem *addr, unsigned offset, u16 data)
	{ __raw_writew(data, addr + offset); }

static inline void musb_writel(void __iomem *addr, unsigned offset, u32 data)
	{ __raw_writel(data, addr + offset); }


#if defined(CONFIG_USB_MUSB_TUSB6010) || defined (CONFIG_USB_MUSB_TUSB6010_MODULE)

/*
 * TUSB6010 doesn't allow 8-bit access; 16-bit access is the minimum.
 */
static inline u8 musb_readb(const void __iomem *addr, unsigned offset)
{
	u16 tmp;
	u8 val;

	tmp = __raw_readw(addr + (offset & ~1));
	if (offset & 1)
		val = (tmp >> 8);
	else
		val = tmp & 0xff;

	return val;
}

static inline void musb_writeb(void __iomem *addr, unsigned offset, u8 data)
{
	u16 tmp;

	tmp = __raw_readw(addr + (offset & ~1));
	if (offset & 1)
		tmp = (data << 8) | (tmp & 0xff);
	else
		tmp = (tmp & 0xff00) | data;

	__raw_writew(tmp, addr + (offset & ~1));
}

#else

static inline u8 musb_readb(const void __iomem *addr, unsigned offset)
	{ return __raw_readb(addr + offset); }

static inline void musb_writeb(void __iomem *addr, unsigned offset, u8 data)
	{ __raw_writeb(data, addr + offset); }

#endif	/* CONFIG_USB_MUSB_TUSB6010 */

#else

static inline u8 musb_readb(const void __iomem *addr, unsigned offset)
	{ return (u8) (bfin_read16(addr + offset)); }

static inline u16 musb_readw(const void __iomem *addr, unsigned offset)
	{ return bfin_read16(addr + offset); }

static inline u32 musb_readl(const void __iomem *addr, unsigned offset)
	{ return (u32) (bfin_read16(addr + offset)); }

static inline void musb_writeb(void __iomem *addr, unsigned offset, u8 data)
	{ bfin_write16(addr + offset, (u16) data); }

static inline void musb_writew(void __iomem *addr, unsigned offset, u16 data)
	{ bfin_write16(addr + offset, data); }

static inline void musb_writel(void __iomem *addr, unsigned offset, u32 data)
	{ bfin_write16(addr + offset, (u16) data); }

#endif /* CONFIG_BLACKFIN */

#endif
