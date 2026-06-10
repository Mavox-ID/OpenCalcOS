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
#ifndef __ASM_ARCH_IMX_ESDHC_H
#define __ASM_ARCH_IMX_ESDHC_H

enum wp_types {
	ESDHC_WP_NONE,		/* no WP, neither controller nor gpio */
	ESDHC_WP_CONTROLLER,	/* mmc controller internal WP */
	ESDHC_WP_GPIO,		/* external gpio pin for WP */
};

enum cd_types {
	ESDHC_CD_NONE,		/* no CD, neither controller nor gpio */
	ESDHC_CD_CONTROLLER,	/* mmc controller internal CD */
	ESDHC_CD_GPIO,		/* external gpio pin for CD */
	ESDHC_CD_PERMANENT,	/* no CD, card permanently wired to host */
};

/**
 * struct esdhc_platform_data - platform data for esdhc on i.MX
 *
 * ESDHC_WP(CD)_CONTROLLER type is not available on i.MX25/35.
 *
 * @wp_gpio:	gpio for write_protect
 * @cd_gpio:	gpio for card_detect interrupt
 * @wp_type:	type of write_protect method (see wp_types enum above)
 * @cd_type:	type of card_detect method (see cd_types enum above)
 */

struct esdhc_platform_data {
	unsigned int wp_gpio;
	unsigned int cd_gpio;
	enum wp_types wp_type;
	enum cd_types cd_type;
};
#endif /* __ASM_ARCH_IMX_ESDHC_H */
