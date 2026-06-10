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
#ifndef STRMDEFS_
#define STRMDEFS_

struct strm_mgr;

struct strm_object;

struct strm_attr {
	void *user_event;
	char *str_event_name;
	void *virt_base;	/* Process virtual base address of
				 * mapped SM */
	u32 virt_size;		/* Size of virtual space in bytes */
	struct dsp_streamattrin *stream_attr_in;
};

struct stream_info {
	enum dsp_strmmode strm_mode;	/* transport mode of
					 * stream(DMA, ZEROCOPY..) */
	u32 segment_id;		/* Segment strm allocs from. 0 is local mem */
	void *virt_base;	/* "      " Stream'process virt base */
	struct dsp_streaminfo *user_strm;	/* User's stream information
						 * returned */
};

#endif /* STRMDEFS_ */
