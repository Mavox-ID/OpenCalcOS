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

/*  ----------------------------------- Host OS */
#include <dspbridge/host_os.h>

/*  ----------------------------------- DSP/BIOS Bridge */
#include <dspbridge/dbdefs.h>

/*  ----------------------------------- This */
#include <dspbridge/uuidutil.h>

static s32 uuid_hex_to_bin(char *buf, s32 len)
{
	s32 i;
	s32 result = 0;
	int value;

	for (i = 0; i < len; i++) {
		value = hex_to_bin(*buf++);
		result *= 16;
		if (value > 0)
			result += value;
	}

	return result;
}

/*
 *  ======== uuid_uuid_from_string ========
 *  Purpose:
 *      Converts a string to a struct dsp_uuid.
 */
void uuid_uuid_from_string(char *sz_uuid, struct dsp_uuid *uuid_obj)
{
	s32 j;

	uuid_obj->data1 = uuid_hex_to_bin(sz_uuid, 8);
	sz_uuid += 8;

	/* Step over underscore */
	sz_uuid++;

	uuid_obj->data2 = (u16) uuid_hex_to_bin(sz_uuid, 4);
	sz_uuid += 4;

	/* Step over underscore */
	sz_uuid++;

	uuid_obj->data3 = (u16) uuid_hex_to_bin(sz_uuid, 4);
	sz_uuid += 4;

	/* Step over underscore */
	sz_uuid++;

	uuid_obj->data4 = (u8) uuid_hex_to_bin(sz_uuid, 2);
	sz_uuid += 2;

	uuid_obj->data5 = (u8) uuid_hex_to_bin(sz_uuid, 2);
	sz_uuid += 2;

	/* Step over underscore */
	sz_uuid++;

	for (j = 0; j < 6; j++) {
		uuid_obj->data6[j] = (u8) uuid_hex_to_bin(sz_uuid, 2);
		sz_uuid += 2;
	}
}
