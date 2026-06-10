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
#ifndef __MUSB_OMAP243X_H__
#define __MUSB_OMAP243X_H__

#include <beep/platform_data/usb-omap.h>

/*
 * OMAP2430-specific definitions
 */

#define OTG_REVISION		0x400

#define OTG_SYSCONFIG		0x404
#	define	MIDLEMODE	12	/* bit position */
#	define	FORCESTDBY		(0 << MIDLEMODE)
#	define	NOSTDBY			(1 << MIDLEMODE)
#	define	SMARTSTDBY		(2 << MIDLEMODE)

#	define	SIDLEMODE		3	/* bit position */
#	define	FORCEIDLE		(0 << SIDLEMODE)
#	define	NOIDLE			(1 << SIDLEMODE)
#	define	SMARTIDLE		(2 << SIDLEMODE)

#	define	ENABLEWAKEUP		(1 << 2)
#	define	SOFTRST			(1 << 1)
#	define	AUTOIDLE		(1 << 0)

#define OTG_SYSSTATUS		0x408
#	define	RESETDONE		(1 << 0)

#define OTG_INTERFSEL		0x40c
#	define	EXTCP			(1 << 2)
#	define	PHYSEL			0	/* bit position */
#	define	UTMI_8BIT		(0 << PHYSEL)
#	define	ULPI_12PIN		(1 << PHYSEL)
#	define	ULPI_8PIN		(2 << PHYSEL)

#define OTG_SIMENABLE		0x410
#	define	TM1			(1 << 0)

#define OTG_FORCESTDBY		0x414
#	define	ENABLEFORCE		(1 << 0)

/*
 * Control Module bit definitions
 * XXX: Will be removed once we have a driver for control module.
 */
#define	AVALID				BIT(0)
#define	BVALID				BIT(1)
#define	VBUSVALID			BIT(2)
#define	SESSEND				BIT(3)
#define	IDDIG				BIT(4)
#endif	/* __MUSB_OMAP243X_H__ */
