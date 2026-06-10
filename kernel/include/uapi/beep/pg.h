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
#define PG_MAGIC	'P'
#define PG_RESET	'Z'
#define PG_COMMAND	'C'

#define PG_MAX_DATA	32768

struct pg_write_hdr {

	char	magic;		/* == PG_MAGIC */
	char	func;		/* PG_RESET or PG_COMMAND */
	int     dlen;		/* number of bytes expected to transfer */
	int     timeout;	/* number of seconds before timeout */
	char	packet[12];	/* packet command */

};

struct pg_read_hdr {

	char	magic;		/* == PG_MAGIC */
	char	scsi;		/* "scsi" status == sense key */
	int	dlen;		/* size of device transfer request */
	int     duration;	/* time in seconds command took */
	char    pad[12];	/* not used */

};

/* end of pg.h */
