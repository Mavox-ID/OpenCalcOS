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
#ifndef DMA_REGISTER_H
#define DMA_REGISTER_H

/*
 *		Direct Memory Access Controller
 */

/* Transmit sizes and respective CHCR register values */
enum {
	XMIT_SZ_8BIT		= 0,
	XMIT_SZ_16BIT		= 1,
	XMIT_SZ_32BIT		= 2,
	XMIT_SZ_64BIT		= 7,
	XMIT_SZ_128BIT		= 3,
	XMIT_SZ_256BIT		= 4,
	XMIT_SZ_512BIT		= 5,
};

/* log2(size / 8) - used to calculate number of transfers */
static const unsigned int dma_ts_shift[] = {
	[XMIT_SZ_8BIT]		= 0,
	[XMIT_SZ_16BIT]		= 1,
	[XMIT_SZ_32BIT]		= 2,
	[XMIT_SZ_64BIT]		= 3,
	[XMIT_SZ_128BIT]	= 4,
	[XMIT_SZ_256BIT]	= 5,
	[XMIT_SZ_512BIT]	= 6,
};

#define TS_LOW_BIT	0x3 /* --xx */
#define TS_HI_BIT	0xc /* xx-- */

#define TS_LOW_SHIFT	(3)
#define TS_HI_SHIFT	(20 - 2)	/* 2 bits for shifted low TS */

#define TS_INDEX2VAL(i) \
	((((i) & TS_LOW_BIT) << TS_LOW_SHIFT) |\
	 (((i) & TS_HI_BIT)  << TS_HI_SHIFT))

#define CHCR_TX(xmit_sz) (DM_FIX | SM_INC | 0x800 | TS_INDEX2VAL((xmit_sz)))
#define CHCR_RX(xmit_sz) (DM_INC | SM_FIX | 0x800 | TS_INDEX2VAL((xmit_sz)))


/*
 *		USB High-Speed DMAC
 */
/* Transmit sizes and respective CHCR register values */
enum {
	USBTS_XMIT_SZ_8BYTE		= 0,
	USBTS_XMIT_SZ_16BYTE		= 1,
	USBTS_XMIT_SZ_32BYTE		= 2,
};

/* log2(size / 8) - used to calculate number of transfers */
static const unsigned int dma_usbts_shift[] = {
	[USBTS_XMIT_SZ_8BYTE]	= 3,
	[USBTS_XMIT_SZ_16BYTE]	= 4,
	[USBTS_XMIT_SZ_32BYTE]	= 5,
};

#define USBTS_LOW_BIT	0x3 /* --xx */
#define USBTS_HI_BIT	0x0 /* ---- */

#define USBTS_LOW_SHIFT	6
#define USBTS_HI_SHIFT	0

#define USBTS_INDEX2VAL(i) (((i) & 3) << 6)

#endif /* DMA_REGISTER_H */
