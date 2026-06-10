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
#ifndef _RTL_PCI_H
#define _RTL_PCI_H

#include <beep/types.h>
#include <beep/pci.h>

static inline void NdisRawWritePortUlong(u32 port,  u32 val)
{
	outl(val, port);
}

static inline void NdisRawWritePortUchar(u32 port,  u8 val)
{
	outb(val, port);
}

static inline void NdisRawReadPortUchar(u32 port, u8 *pval)
{
	*pval = inb(port);
}

static inline void NdisRawReadPortUshort(u32 port, u16 *pval)
{
	*pval = inw(port);
}

static inline void NdisRawReadPortUlong(u32 port, u32 *pval)
{
	*pval = inl(port);
}

struct mp_adapter {
	u8		LinkCtrlReg;

	u8		BusNumber;
	u8		DevNumber;
	u8		FuncNumber;

	u8		PciBridgeBusNum;
	u8		PciBridgeDevNum;
	u8		PciBridgeFuncNum;
	u8		PciBridgeVendor;
	u16		PciBridgeVendorId;
	u16		PciBridgeDeviceId;
	u8		PciBridgePCIeHdrOffset;
	u8		PciBridgeLinkCtrlReg;
};

struct rt_pci_capab_header {
	unsigned char   CapabilityID;
	unsigned char   Next;
};

#define PCI_MAX_BRIDGE_NUMBER				255
#define PCI_MAX_DEVICES						32
#define PCI_MAX_FUNCTION					8

#define PCI_CONF_ADDRESS					0x0CF8
#define PCI_CONF_DATA						0x0CFC

#define	PCI_CLASS_BRIDGE_DEV				0x06
#define	PCI_SUBCLASS_BR_PCI_TO_PCI		0x04

#define	U1DONTCARE						0xFF
#define	U2DONTCARE						0xFFFF
#define	U4DONTCARE						0xFFFFFFFF

#define	INTEL_VENDOR_ID					0x8086
#define	SIS_VENDOR_ID						0x1039
#define	ATI_VENDOR_ID						0x1002
#define	ATI_DEVICE_ID						0x7914
#define	AMD_VENDOR_ID						0x1022

#define PCI_CAPABILITY_ID_PCI_EXPRESS		0x10

struct net_device;
bool rtl8192_pci_findadapter(struct pci_dev *pdev, struct net_device *dev);

#endif
