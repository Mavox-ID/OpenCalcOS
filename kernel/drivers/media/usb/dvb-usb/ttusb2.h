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
#ifndef _DVB_USB_TTUSB2_H_
#define _DVB_USB_TTUSB2_H_

/* TTUSB protocol
 *
 * always to messages (out/in)
 * out message:
 * 0xaa <id> <cmdbyte> <datalen> <data...>
 *
 * in message (complete block is always 0x40 bytes long)
 * 0x55 <id> <cmdbyte> <datalen> <data...>
 *
 * id is incremented for each transaction
 */

#define CMD_DSP_DOWNLOAD    0x13
/* out data: <byte>[28]
 * last block must be empty */

#define CMD_DSP_BOOT        0x14
/* out data: nothing */

#define CMD_POWER           0x15
/* out data: <on=1/off=0> */

#define CMD_LNB             0x16
/* out data: <power=1> <18V=0,13V=1> <tone> <??=1> <??=1> */

#define CMD_GET_VERSION     0x17
/* in  data: <version_byte>[5] */

#define CMD_DISEQC          0x18
/* out data: <master=0xff/burst=??> <cmdlen> <cmdbytes>[cmdlen] */

#define CMD_PID_ENABLE      0x22
/* out data: <index> <type: ts=1/sec=2> <pid msb> <pid lsb> */

#define CMD_PID_DISABLE     0x23
/* out data: <index> */

#define CMD_FILTER_ENABLE   0x24
/* out data: <index> <pid_idx> <filter>[12] <mask>[12] */

#define CMD_FILTER_DISABLE  0x25
/* out data: <index> */

#define CMD_GET_DSP_VERSION 0x26
/* in  data: <version_byte>[28] */

#define CMD_I2C_XFER        0x31
/* out data: <addr << 1> <sndlen> <rcvlen> <data>[sndlen]
 * in  data: <addr << 1> <sndlen> <rcvlen> <data>[rcvlen] */

#define CMD_I2C_BITRATE     0x32
/* out data: <default=0> */

#endif
