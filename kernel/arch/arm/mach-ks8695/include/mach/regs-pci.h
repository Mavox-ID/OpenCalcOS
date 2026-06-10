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
#define KS8695_PCI_OFFSET	(0xF0000 + 0x2000)
#define KS8695_PCI_VA		(KS8695_IO_VA + KS8695_PCI_OFFSET)
#define KS8695_PCI_PA		(KS8695_IO_PA + KS8695_PCI_OFFSET)


#define KS8695_CRCFID		(0x000)		/* Configuration: Identification */
#define KS8695_CRCFCS		(0x004)		/* Configuration: Command and Status */
#define KS8695_CRCFRV		(0x008)		/* Configuration: Revision */
#define KS8695_CRCFLT		(0x00C)		/* Configuration: Latency Timer */
#define KS8695_CRCBMA		(0x010)		/* Configuration: Base Memory Address */
#define KS8695_CRCSID		(0x02C)		/* Configuration: Subsystem ID */
#define KS8695_CRCFIT		(0x03C)		/* Configuration: Interrupt */
#define KS8695_PBCA		(0x100)		/* Bridge Configuration Address */
#define KS8695_PBCD		(0x104)		/* Bridge Configuration Data */
#define KS8695_PBM		(0x200)		/* Bridge Mode */
#define KS8695_PBCS		(0x204)		/* Bridge Control and Status */
#define KS8695_PMBA		(0x208)		/* Bridge Memory Base Address */
#define KS8695_PMBAC		(0x20C)		/* Bridge Memory Base Address Control */
#define KS8695_PMBAM		(0x210)		/* Bridge Memory Base Address Mask */
#define KS8695_PMBAT		(0x214)		/* Bridge Memory Base Address Translation */
#define KS8695_PIOBA		(0x218)		/* Bridge I/O Base Address */
#define KS8695_PIOBAC		(0x21C)		/* Bridge I/O Base Address Control */
#define KS8695_PIOBAM		(0x220)		/* Bridge I/O Base Address Mask */
#define KS8695_PIOBAT		(0x224)		/* Bridge I/O Base Address Translation */


/* Configuration: Identification */

/* Configuration: Command and Status */

/* Configuration: Revision */



#define CFRV_GUEST		(1 << 23)

#define PBCA_TYPE1		(1)
#define PBCA_ENABLE		(1 << 31)


