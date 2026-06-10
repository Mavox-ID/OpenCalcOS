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
#ifndef _ASM_390_MONWRITER_H
#define _ASM_390_MONWRITER_H

/* mon_function values */
#define MONWRITE_START_INTERVAL	0x00 /* start interval recording */
#define MONWRITE_STOP_INTERVAL	0x01 /* stop interval or config recording */
#define MONWRITE_GEN_EVENT	0x02 /* generate event record */
#define MONWRITE_START_CONFIG	0x03 /* start configuration recording */

/* the header the app uses in its write() data */
struct monwrite_hdr {
	unsigned char mon_function;
	unsigned short applid;
	unsigned char record_num;
	unsigned short version;
	unsigned short release;
	unsigned short mod_level;
	unsigned short datalen;
	unsigned char hdrlen;

} __attribute__((packed));

#endif /* _ASM_390_MONWRITER_H */
