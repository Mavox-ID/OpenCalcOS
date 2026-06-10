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
#ifndef _WM8505FB_REGS_H
#define _WM8505FB_REGS_H

/*
 * Color space select register, default value 0x1c
 *   BIT0 GOVRH_DVO_YUV2RGB_ENABLE
 *   BIT1 GOVRH_VGA_YUV2RGB_ENABLE
 *   BIT2 GOVRH_RGB_MODE
 *   BIT3 GOVRH_DAC_CLKINV
 *   BIT4 GOVRH_BLANK_ZERO
 */
#define WMT_GOVR_COLORSPACE	0x1e4
/*
 * Another colorspace select register, default value 1
 *   BIT0 GOVRH_DVO_RGB
 *   BIT1 GOVRH_DVO_YUV422
 */
#define WMT_GOVR_COLORSPACE1	 0x30

#define WMT_GOVR_CONTRAST	0x1b8
#define WMT_GOVR_BRGHTNESS	0x1bc /* incompatible with RGB? */

/* Framubeffer address */
#define WMT_GOVR_FBADDR		 0x90
#define WMT_GOVR_FBADDR1	 0x94 /* UV offset in YUV mode */

/* Offset of visible window */
#define WMT_GOVR_XPAN		 0xa4
#define WMT_GOVR_YPAN		 0xa0

#define WMT_GOVR_XRES		 0x98
#define WMT_GOVR_XRES_VIRTUAL	 0x9c

#define WMT_GOVR_MIF_ENABLE	 0x80
#define WMT_GOVR_FHI		 0xa8
#define WMT_GOVR_REG_UPDATE	 0xe4

/*
 *   BIT0 GOVRH_DVO_OUTWIDTH
 *   BIT1 GOVRH_DVO_SYNC_POLAR
 *   BIT2 GOVRH_DVO_ENABLE
 */
#define WMT_GOVR_DVO_SET	0x148

/* Timing generator? */
#define WMT_GOVR_TG		0x100

/* Timings */
#define WMT_GOVR_TIMING_H_ALL	0x108
#define WMT_GOVR_TIMING_V_ALL	0x10c
#define WMT_GOVR_TIMING_V_START	0x110
#define WMT_GOVR_TIMING_V_END	0x114
#define WMT_GOVR_TIMING_H_START	0x118
#define WMT_GOVR_TIMING_H_END	0x11c
#define WMT_GOVR_TIMING_V_SYNC	0x128
#define WMT_GOVR_TIMING_H_SYNC	0x12c

#endif /* _WM8505FB_REGS_H */
