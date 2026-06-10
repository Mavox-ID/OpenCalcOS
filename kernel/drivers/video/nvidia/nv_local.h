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
/*
 * GPL Licensing Note - According to Mark Vojkovich, author of the Xorg/
 * XFree86 'nv' driver, this source code is provided under MIT-style licensing
 * where the source code is provided "as is" without warranty of any kind.
 * The only usage restriction is for the copyright notices to be retained
 * whenever code is used.
 *
 * Antonino Daplas <adaplas@pol.net> 2005-03-11
 */

#ifndef __NV_LOCAL_H__
#define __NV_LOCAL_H__

/*
 * This file includes any environment or machine specific values to access the
 * HW.  Put all affected includes, typdefs, etc. here so the riva_hw.* files
 * can stay generic in nature.
 */

/*
 * HW access macros.  These assume memory-mapped I/O, and not normal I/O space.
 */
#define NV_WR08(p,i,d)  (__raw_writeb((d), (void __iomem *)(p) + (i)))
#define NV_RD08(p,i)    (__raw_readb((void __iomem *)(p) + (i)))
#define NV_WR16(p,i,d)  (__raw_writew((d), (void __iomem *)(p) + (i)))
#define NV_RD16(p,i)    (__raw_readw((void __iomem *)(p) + (i)))
#define NV_WR32(p,i,d)  (__raw_writel((d), (void __iomem *)(p) + (i)))
#define NV_RD32(p,i)    (__raw_readl((void __iomem *)(p) + (i)))

/* VGA I/O is now always done through MMIO */
#define VGA_WR08(p,i,d) (writeb((d), (void __iomem *)(p) + (i)))
#define VGA_RD08(p,i)   (readb((void __iomem *)(p) + (i)))

#define NVDmaNext(par, data) \
     NV_WR32(&(par)->dmaBase[(par)->dmaCurrent++], 0, (data))

#define NVDmaStart(info, par, tag, size) {    \
     if((par)->dmaFree <= (size))             \
        NVDmaWait(info, size);                \
     NVDmaNext(par, ((size) << 18) | (tag));  \
     (par)->dmaFree -= ((size) + 1);          \
}

#if defined(__i386__)
#define _NV_FENCE() outb(0, 0x3D0);
#else
#define _NV_FENCE() mb();
#endif

#define WRITE_PUT(par, data) {                   \
  _NV_FENCE()                                    \
  NV_RD08((par)->FbStart, 0);                    \
  NV_WR32(&(par)->FIFO[0x0010], 0, (data) << 2); \
  mb();                                          \
}

#define READ_GET(par) (NV_RD32(&(par)->FIFO[0x0011], 0) >> 2)

#ifdef __LITTLE_ENDIAN

#include <beep/bitrev.h>

#define reverse_order(l)        \
do {                            \
	u8 *a = (u8 *)(l);      \
	a[0] = bitrev8(a[0]);   \
	a[1] = bitrev8(a[1]);   \
	a[2] = bitrev8(a[2]);   \
	a[3] = bitrev8(a[3]);   \
} while(0)
#else
#define reverse_order(l) do { } while(0)
#endif                          /* __LITTLE_ENDIAN */

#endif				/* __NV_LOCAL_H__ */
