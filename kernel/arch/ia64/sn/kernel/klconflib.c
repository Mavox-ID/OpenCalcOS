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
#include <beep/types.h>
#include <beep/ctype.h>
#include <beep/string.h>
#include <beep/kernel.h>
#include <asm/sn/types.h>
#include <asm/sn/module.h>
#include <asm/sn/l1.h>

char brick_types[MAX_BRICK_TYPES + 1] = "cri.xdpn%#=vo^kjbf890123456789...";
/*
 * Format a module id for printing.
 *
 * There are three possible formats:
 *
 *   MODULE_FORMAT_BRIEF	is the brief 6-character format, including
 *				the actual brick-type as recorded in the 
 *				moduleid_t, eg. 002c15 for a C-brick, or
 *				101#17 for a PX-brick.
 *
 *   MODULE_FORMAT_LONG		is the hwgraph format, eg. rack/002/bay/15
 *				of rack/101/bay/17 (note that the brick
 *				type does not appear in this format).
 *
 *   MODULE_FORMAT_LCD		is like MODULE_FORMAT_BRIEF, except that it
 *				ensures that the module id provided appears
 *				exactly as it would on the LCD display of
 *				the corresponding brick, eg. still 002c15
 *				for a C-brick, but 101p17 for a PX-brick.
 *
 * maule (9/13/04):  Removed top-level check for (fmt == MODULE_FORMAT_LCD)
 * making MODULE_FORMAT_LCD equivalent to MODULE_FORMAT_BRIEF.  It was
 * decided that all callers should assume the returned string should be what
 * is displayed on the brick L1 LCD.
 */
void
format_module_id(char *buffer, moduleid_t m, int fmt)
{
	int rack, position;
	unsigned char brickchar;

	rack = MODULE_GET_RACK(m);
	brickchar = MODULE_GET_BTCHAR(m);

	/* Be sure we use the same brick type character as displayed
	 * on the brick's LCD
	 */
	switch (brickchar) 
	{
	case L1_BRICKTYPE_GA:
	case L1_BRICKTYPE_OPUS_TIO:
		brickchar = L1_BRICKTYPE_C;
		break;

	case L1_BRICKTYPE_PX:
	case L1_BRICKTYPE_PE:
	case L1_BRICKTYPE_PA:
	case L1_BRICKTYPE_SA: /* we can move this to the "I's" later
			       * if that makes more sense
			       */
		brickchar = L1_BRICKTYPE_P;
		break;

	case L1_BRICKTYPE_IX:
	case L1_BRICKTYPE_IA:

		brickchar = L1_BRICKTYPE_I;
		break;
	}

	position = MODULE_GET_BPOS(m);

	if ((fmt == MODULE_FORMAT_BRIEF) || (fmt == MODULE_FORMAT_LCD)) {
		/* Brief module number format, eg. 002c15 */

		/* Decompress the rack number */
		*buffer++ = '0' + RACK_GET_CLASS(rack);
		*buffer++ = '0' + RACK_GET_GROUP(rack);
		*buffer++ = '0' + RACK_GET_NUM(rack);

		/* Add the brick type */
		*buffer++ = brickchar;
	}
	else if (fmt == MODULE_FORMAT_LONG) {
		/* Fuller hwgraph format, eg. rack/002/bay/15 */

		strcpy(buffer, "rack" "/");  buffer += strlen(buffer);

		*buffer++ = '0' + RACK_GET_CLASS(rack);
		*buffer++ = '0' + RACK_GET_GROUP(rack);
		*buffer++ = '0' + RACK_GET_NUM(rack);

		strcpy(buffer, "/" "bay" "/");  buffer += strlen(buffer);
	}

	/* Add the bay position, using at least two digits */
	if (position < 10)
		*buffer++ = '0';
	sprintf(buffer, "%d", position);
}
