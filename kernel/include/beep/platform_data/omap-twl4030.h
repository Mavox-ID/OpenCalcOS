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
#ifndef _OMAP_TWL4030_H_
#define _OMAP_TWL4030_H_

/* To select if only one channel is connected in a stereo port */
#define OMAP_TWL4030_LEFT	(1 << 0)
#define OMAP_TWL4030_RIGHT	(1 << 1)

struct omap_tw4030_pdata {
	const char *card_name;
	/* Voice port is connected to McBSP3 */
	bool voice_connected;

	/* The driver will parse the connection flags if this flag is set */
	bool	custom_routing;
	/* Flags to indicate connected audio ports. */
	u8	has_hs;
	u8	has_hf;
	u8	has_predriv;
	u8	has_carkit;
	bool	has_ear;

	bool	has_mainmic;
	bool	has_submic;
	bool	has_hsmic;
	bool	has_carkitmic;
	bool	has_digimic0;
	bool	has_digimic1;
	u8	has_linein;

	/* Jack detect GPIO or  <= 0 if it is not implemented */
	int jack_detect;
};

#endif /* _OMAP_TWL4030_H_ */
