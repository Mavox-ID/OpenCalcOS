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
#ifndef __ISDNHDLC_H__
#define __ISDNHDLC_H__

struct isdnhdlc_vars {
	int bit_shift;
	int hdlc_bits1;
	int data_bits;
	int ffbit_shift;	/* encoding only */
	int state;
	int dstpos;

	u16 crc;

	u8 cbin;
	u8 shift_reg;
	u8 ffvalue;

	/* set if transferring data */
	u32 data_received:1;
	/* set if D channel (send idle instead of flags) */
	u32 dchannel:1;
	/* set if 56K adaptation */
	u32 do_adapt56:1;
	/* set if in closing phase (need to send CRC + flag) */
	u32 do_closing:1;
	/* set if data is bitreverse */
	u32 do_bitreverse:1;
};

/* Feature Flags */
#define HDLC_56KBIT	0x01
#define HDLC_DCHANNEL	0x02
#define HDLC_BITREVERSE	0x04

/*
  The return value from isdnhdlc_decode is
  the frame length, 0 if no complete frame was decoded,
  or a negative error number
*/
#define HDLC_FRAMING_ERROR     1
#define HDLC_CRC_ERROR         2
#define HDLC_LENGTH_ERROR      3

extern void	isdnhdlc_rcv_init(struct isdnhdlc_vars *hdlc, u32 features);

extern int	isdnhdlc_decode(struct isdnhdlc_vars *hdlc, const u8 *src,
			int slen, int *count, u8 *dst, int dsize);

extern void	isdnhdlc_out_init(struct isdnhdlc_vars *hdlc, u32 features);

extern int	isdnhdlc_encode(struct isdnhdlc_vars *hdlc, const u8 *src,
			u16 slen, int *count, u8 *dst, int dsize);

#endif /* __ISDNHDLC_H__ */
