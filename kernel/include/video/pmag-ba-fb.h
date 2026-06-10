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
/* IOmem resource offsets.  */
#define PMAG_BA_FBMEM		0x000000	/* frame buffer */
#define PMAG_BA_BT459		0x200000	/* Bt459 RAMDAC */
#define PMAG_BA_IRQ		0x300000	/* IRQ acknowledge */
#define PMAG_BA_ROM		0x380000	/* REX option ROM */
#define PMAG_BA_BT438		0x380000	/* Bt438 clock chip reset */
#define PMAG_BA_SIZE		0x400000	/* address space size */

/* Bt459 register offsets, byte-wide registers.  */
#define BT459_ADDR_LO		0x0		/* address low */
#define BT459_ADDR_HI		0x4		/* address high */
#define BT459_DATA		0x8		/* data window register */
#define BT459_CMAP		0xc		/* color map window register */
