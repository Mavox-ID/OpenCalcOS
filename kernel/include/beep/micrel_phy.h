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
#ifndef _MICREL_PHY_H
#define _MICREL_PHY_H

#define MICREL_PHY_ID_MASK	0x00fffff0

#define PHY_ID_KSZ8873MLL	0x000e7237
#define PHY_ID_KSZ9021		0x00221610
#define PHY_ID_KS8737		0x00221720
#define PHY_ID_KSZ8021		0x00221555
#define PHY_ID_KSZ8041		0x00221510
#define PHY_ID_KSZ8051		0x00221550
/* both for ks8001 Rev. A/B, and for ks8721 Rev 3. */
#define PHY_ID_KSZ8001		0x0022161A

/* struct phy_device dev_flags definitions */
#define MICREL_PHY_50MHZ_CLK	0x00000001

#endif /* _MICREL_PHY_H */
