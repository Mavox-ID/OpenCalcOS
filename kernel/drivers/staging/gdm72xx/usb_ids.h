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
#ifndef __USB_IDS_H__
#define __USB_IDS_H__

/*You can replace vendor-ID as yours.*/
#define GCT_VID			0x1076

/*You can replace product-ID as yours.*/
#define GCT_PID1			0x7e00
#define GCT_PID2			0x7f00

#define USB_DEVICE_ID_MATCH_DEVICE_INTERFACE	\
	(USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_INT_CLASS)

#define USB_DEVICE_INTF(vend, prod, intf)	\
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE_INTERFACE,	\
	.idVendor = (vend), .idProduct = (prod), .bInterfaceClass = (intf)

#define EMERGENCY_PID		0x720f
#define BL_PID_MASK			0xffc0

#define USB_DEVICE_BOOTLOADER(vid, pid)	\
	{USB_DEVICE((vid), ((pid)&BL_PID_MASK)|B_DOWNLOAD)},	\
	{USB_DEVICE((vid), ((pid)&BL_PID_MASK)|B_DOWNLOAD|B_DIFF_DL_DRV)}

#define USB_DEVICE_CDC_DATA(vid, pid)	\
	{USB_DEVICE_INTF((vid), (pid), USB_CLASS_CDC_DATA)}

static const struct usb_device_id id_table[] = {
	USB_DEVICE_BOOTLOADER(GCT_VID, GCT_PID1),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0x1),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0x2),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0x3),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0x4),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0x5),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0x6),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0x7),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0x8),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0x9),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0xa),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0xb),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0xc),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0xd),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0xe),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID1+0xf),

	USB_DEVICE_BOOTLOADER(GCT_VID, GCT_PID2),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0x1),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0x2),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0x3),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0x4),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0x5),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0x6),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0x7),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0x8),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0x9),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0xa),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0xb),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0xc),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0xd),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0xe),
	USB_DEVICE_CDC_DATA(GCT_VID, GCT_PID2+0xf),

	{USB_DEVICE(GCT_VID, EMERGENCY_PID)},
	{ }
};

#endif /* __USB_IDS_H__ */
