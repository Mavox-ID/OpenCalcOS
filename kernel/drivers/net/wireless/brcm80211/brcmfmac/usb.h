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
#ifndef BRCMFMAC_USB_H
#define BRCMFMAC_USB_H

enum brcmf_usb_state {
	BRCMFMAC_USB_STATE_DOWN,
	BRCMFMAC_USB_STATE_DL_FAIL,
	BRCMFMAC_USB_STATE_DL_DONE,
	BRCMFMAC_USB_STATE_UP,
	BRCMFMAC_USB_STATE_SLEEP
};

struct brcmf_stats {
	u32 tx_ctlpkts;
	u32 tx_ctlerrs;
	u32 rx_ctlpkts;
	u32 rx_ctlerrs;
};

struct brcmf_usbdev {
	struct brcmf_bus *bus;
	struct brcmf_usbdev_info *devinfo;
	enum brcmf_usb_state state;
	struct brcmf_stats stats;
	int ntxq, nrxq, rxsize;
	u32 bus_mtu;
	int devid;
	int chiprev; /* chip revsion number */
};

/* IO Request Block (IRB) */
struct brcmf_usbreq {
	struct list_head list;
	struct brcmf_usbdev_info *devinfo;
	struct urb *urb;
	struct sk_buff  *skb;
};

#endif /* BRCMFMAC_USB_H */
