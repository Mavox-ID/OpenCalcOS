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
#ifndef OMAP_ARCH_WAKEUPGEN_H
#define OMAP_ARCH_WAKEUPGEN_H

/* OMAP4 and OMAP5 has same base address */
#define OMAP_WKUPGEN_BASE			0x48281000

#define OMAP_WKG_CONTROL_0			0x00
#define OMAP_WKG_ENB_A_0			0x10
#define OMAP_WKG_ENB_B_0			0x14
#define OMAP_WKG_ENB_C_0			0x18
#define OMAP_WKG_ENB_D_0			0x1c
#define OMAP_WKG_ENB_E_0			0x20
#define OMAP_WKG_ENB_A_1			0x410
#define OMAP_WKG_ENB_B_1			0x414
#define OMAP_WKG_ENB_C_1			0x418
#define OMAP_WKG_ENB_D_1			0x41c
#define OMAP_WKG_ENB_E_1			0x420
#define OMAP_AUX_CORE_BOOT_0			0x800
#define OMAP_AUX_CORE_BOOT_1			0x804
#define OMAP_PTMSYNCREQ_MASK			0xc00
#define OMAP_PTMSYNCREQ_EN			0xc04
#define OMAP_TIMESTAMPCYCLELO			0xc08
#define OMAP_TIMESTAMPCYCLEHI			0xc0c

extern int __init omap_wakeupgen_init(void);
extern void __iomem *omap_get_wakeupgen_base(void);
extern int omap_secure_apis_support(void);
#endif
