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
#ifndef _MWIFIEX_USB_H
#define _MWIFIEX_USB_H

#include <beep/usb.h>

#define USB8797_VID		0x1286
#define USB8797_PID_1		0x2043
#define USB8797_PID_2		0x2044

#define USB8797_FW_DNLD		1
#define USB8797_FW_READY	2
#define USB8797_FW_MAX_RETRY	3

#define MWIFIEX_TX_DATA_URB	6
#define MWIFIEX_RX_DATA_URB	6
#define MWIFIEX_USB_TIMEOUT	100

#define USB8797_DEFAULT_FW_NAME	"mrvl/usb8797_uapsta.bin"

#define FW_DNLD_TX_BUF_SIZE	620
#define FW_DNLD_RX_BUF_SIZE	2048
#define FW_HAS_LAST_BLOCK	0x00000004

#define FW_DATA_XMIT_SIZE \
	(sizeof(struct fw_header) + dlen + sizeof(u32))

struct urb_context {
	struct mwifiex_adapter *adapter;
	struct sk_buff *skb;
	struct urb *urb;
	u8 ep;
};

struct usb_card_rec {
	struct mwifiex_adapter *adapter;
	struct usb_device *udev;
	struct usb_interface *intf;
	u8 rx_cmd_ep;
	struct urb_context rx_cmd;
	atomic_t rx_cmd_urb_pending;
	struct urb_context rx_data_list[MWIFIEX_RX_DATA_URB];
	u8 usb_boot_state;
	u8 rx_data_ep;
	atomic_t rx_data_urb_pending;
	u8 tx_data_ep;
	u8 tx_cmd_ep;
	atomic_t tx_data_urb_pending;
	atomic_t tx_cmd_urb_pending;
	int bulk_out_maxpktsize;
	struct urb_context tx_cmd;
	int tx_data_ix;
	struct urb_context tx_data_list[MWIFIEX_TX_DATA_URB];
};

struct fw_header {
	__le32 dnld_cmd;
	__le32 base_addr;
	__le32 data_len;
	__le32 crc;
};

struct fw_sync_header {
	__le32 cmd;
	__le32 seq_num;
};

struct fw_data {
	struct fw_header fw_hdr;
	__le32 seq_num;
	u8 data[1];
};

/* This function is called after the card has woken up. */
static inline int
mwifiex_pm_wakeup_card_complete(struct mwifiex_adapter *adapter)
{
	return 0;
}

#endif /*_MWIFIEX_USB_H */
