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
#ifndef _VNIC_RSS_H_
#define _VNIC_RSS_H_

/* RSS key array */
union vnic_rss_key {
	struct {
		u8 b[10];
		u8 b_pad[6];
	} key[4];
	u64 raw[8];
};

/* RSS cpu array */
union vnic_rss_cpu {
	struct {
		u8 b[4] ;
		u8 b_pad[4];
	} cpu[32];
	u64 raw[32];
};

#endif /* _VNIC_RSS_H_ */
