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
#ifndef __NLM_HAL_USB_H__
#define __NLM_HAL_USB_H__

#define USB_CTL_0			0x01
#define USB_PHY_0			0x0A
#define USB_PHY_RESET			0x01
#define USB_PHY_PORT_RESET_0		0x10
#define USB_PHY_PORT_RESET_1		0x20
#define USB_CONTROLLER_RESET		0x01
#define USB_INT_STATUS			0x0E
#define USB_INT_EN			0x0F
#define USB_PHY_INTERRUPT_EN		0x01
#define USB_OHCI_INTERRUPT_EN		0x02
#define USB_OHCI_INTERRUPT1_EN		0x04
#define USB_OHCI_INTERRUPT2_EN		0x08
#define USB_CTRL_INTERRUPT_EN		0x10

#ifndef __ASSEMBLY__

#define nlm_read_usb_reg(b, r)			nlm_read_reg(b, r)
#define nlm_write_usb_reg(b, r, v)		nlm_write_reg(b, r, v)
#define nlm_get_usb_pcibase(node, inst)		\
	nlm_pcicfg_base(XLP_IO_USB_OFFSET(node, inst))
#define nlm_get_usb_hcd_base(node, inst)	\
	nlm_xkphys_map_pcibar0(nlm_get_usb_pcibase(node, inst))
#define nlm_get_usb_regbase(node, inst)		\
	(nlm_get_usb_pcibase(node, inst) + XLP_IO_PCI_HDRSZ)

#endif
#endif /* __NLM_HAL_USB_H__ */
