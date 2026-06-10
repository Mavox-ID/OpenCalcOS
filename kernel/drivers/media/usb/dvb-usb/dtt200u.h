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
#ifndef _DVB_USB_DTT200U_H_
#define _DVB_USB_DTT200U_H_

#define DVB_USB_LOG_PREFIX "dtt200u"

#include "dvb-usb.h"

extern int dvb_usb_dtt200u_debug;
#define deb_info(args...) dprintk(dvb_usb_dtt200u_debug,0x01,args)
#define deb_xfer(args...) dprintk(dvb_usb_dtt200u_debug,0x02,args)

/* guessed protocol description (reverse engineered):
 * read
 *  00 - USB type 0x02 for usb2.0, 0x01 for usb1.1
 *  88 - locking 2 bytes (0x80 0x40 == no signal, 0x89 0x20 == nice signal)
 */

#define GET_SPEED		0x00
#define GET_TUNE_STATUS		0x81
#define GET_RC_CODE		0x84
#define GET_CONFIGURATION	0x88
#define GET_AGC			0x89
#define GET_SNR			0x8a
#define GET_VIT_ERR_CNT		0x8c
#define GET_RS_ERR_CNT		0x8d
#define GET_RS_UNCOR_BLK_CNT	0x8e

/* write
 *  01 - init
 *  02 - frequency (divided by 250000)
 *  03 - bandwidth
 *  04 - pid table (index pid(7:0) pid(12:8))
 *  05 - reset the pid table
 *  08 - transfer switch
 */

#define SET_INIT		0x01
#define SET_RF_FREQ		0x02
#define SET_BANDWIDTH		0x03
#define SET_PID_FILTER		0x04
#define RESET_PID_FILTER	0x05
#define SET_STREAMING		0x08

extern struct dvb_frontend * dtt200u_fe_attach(struct dvb_usb_device *d);

#endif
