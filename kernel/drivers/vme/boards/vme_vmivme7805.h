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
#ifndef _VMIVME_7805_H
#define _VMIVME_7805_H

#ifndef PCI_VENDOR_ID_VMIC
#define PCI_VENDOR_ID_VMIC		0x114A
#endif

#ifndef PCI_DEVICE_ID_VTIMR
#define PCI_DEVICE_ID_VTIMR		0x0004
#endif

#define VME_CONTROL			0x0000
#define BM_VME_CONTROL_MASTER_ENDIAN	0x0001
#define BM_VME_CONTROL_SLAVE_ENDIAN	0x0002
#define BM_VME_CONTROL_ABLE		0x0004
#define BM_VME_CONTROL_BERRI		0x0040
#define BM_VME_CONTROL_BERRST		0x0080
#define BM_VME_CONTROL_BPENA		0x0400
#define BM_VME_CONTROL_VBENA		0x0800

#endif /* _VMIVME_7805_H */

