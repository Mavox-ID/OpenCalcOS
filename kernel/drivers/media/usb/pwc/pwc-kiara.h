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
/* Entries for the Kiara (730/740/750) camera */

#ifndef PWC_KIARA_H
#define PWC_KIARA_H

#include "pwc.h"

#define PWC_FPS_MAX_KIARA 6

struct Kiara_table_entry
{
	char alternate;			/* USB alternate interface */
	unsigned short packetsize;	/* Normal packet size */
	unsigned short bandlength;	/* Bandlength when decompressing */
	unsigned char mode[12];		/* precomputed mode settings for cam */
};

extern const struct Kiara_table_entry Kiara_table[PSZ_MAX][PWC_FPS_MAX_KIARA][4];
extern const unsigned int KiaraRomTable[8][2][16][8];
extern const unsigned int Kiara_fps_vector[PWC_FPS_MAX_KIARA];

#endif


