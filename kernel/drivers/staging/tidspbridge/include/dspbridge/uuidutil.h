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
#ifndef UUIDUTIL_
#define UUIDUTIL_

#define MAXUUIDLEN  37

/*
 *  ======== uuid_uuid_from_string ========
 *  Purpose:
 *      Converts an ANSI string to a dsp_uuid.
 *  Parameters:
 *      sz_uuid:    Pointer to a string that represents a dsp_uuid object.
 *      uuid_obj:      Pointer to a dsp_uuid object.
 *  Returns:
 *  Requires:
 *      uuid_obj & sz_uuid are non-NULL values.
 *  Ensures:
 *  Details:
 *      We assume the string representation of a UUID has the following format:
 *      "12345678_1234_1234_1234_123456789abc".
 */
extern void uuid_uuid_from_string(char *sz_uuid,
				  struct dsp_uuid *uuid_obj);

#endif /* UUIDUTIL_ */
