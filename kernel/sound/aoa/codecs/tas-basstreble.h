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
#define TAS3004_TREBLE_MIN	0
#define TAS3004_TREBLE_MAX	72
#define TAS3004_BASS_MIN	0
#define TAS3004_BASS_MAX	72
#define TAS3004_TREBLE_ZERO	36
#define TAS3004_BASS_ZERO	36

static u8 tas3004_treble_table[] = {
	150, /* -18 dB */
	149,
	148,
	147,
	146,
	145,
	144,
	143,
	142,
	141,
	140,
	139,
	138,
	137,
	136,
	135,
	134,
	133,
	132,
	131,
	130,
	129,
	128,
	127,
	126,
	125,
	124,
	123,
	122,
	121,
	120,
	119,
	118,
	117,
	116,
	115,
	114, /* 0 dB */
	113,
	112,
	111,
	109,
	108,
	107,
	105,
	104,
	103,
	101,
	99,
	98,
	96,
	93,
	91,
	89,
	86,
	83,
	81,
	77,
	74,
	71,
	67,
	63,
	59,
	54,
	49,
	44,
	38,
	32,
	26,
	19,
	10,
	4,
	2,
	1, /* +18 dB */
};

static inline u8 tas3004_treble(int idx)
{
	return tas3004_treble_table[idx];
}

/* I only save the difference here to the treble table
 * so that the binary is smaller...
 * I have also ignored completely differences of
 * +/- 1
 */
static s8 tas3004_bass_diff_to_treble[] = {
	2, /* 7 dB, offset 50 */
	2,
	2,
	2,
	2,
	1,
	2,
	2,
	2,
	3,
	4,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	14,
	13,
	8,
	1, /* 18 dB */
};

static inline u8 tas3004_bass(int idx)
{
	u8 result = tas3004_treble_table[idx];

	if (idx >= 50)
		result += tas3004_bass_diff_to_treble[idx-50];
	return result;
}
