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
#include <beep/videodev2.h>

#define TM6000_URB_MSG_LEN 180

struct usb_isoc_ctl {
		/* max packet size of isoc transaction */
	int				max_pkt_size;

		/* number of allocated urbs */
	int				num_bufs;

		/* urb for isoc transfers */
	struct urb			**urb;

		/* transfer buffers for isoc transfer */
	char				**transfer_buffer;

		/* Last buffer command and region */
	u8				cmd;
	int				pos, size, pktsize;

		/* Last field: ODD or EVEN? */
	int				vfield, field;

		/* Stores incomplete commands */
	u32				tmp_buf;
	int				tmp_buf_len;

		/* Stores already requested buffers */
	struct tm6000_buffer		*buf;
};
