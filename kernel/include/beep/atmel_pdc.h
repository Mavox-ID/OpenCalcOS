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
#ifndef ATMEL_PDC_H
#define ATMEL_PDC_H

#define ATMEL_PDC_RPR		0x100	/* Receive Pointer Register */
#define ATMEL_PDC_RCR		0x104	/* Receive Counter Register */
#define ATMEL_PDC_TPR		0x108	/* Transmit Pointer Register */
#define ATMEL_PDC_TCR		0x10c	/* Transmit Counter Register */
#define ATMEL_PDC_RNPR		0x110	/* Receive Next Pointer Register */
#define ATMEL_PDC_RNCR		0x114	/* Receive Next Counter Register */
#define ATMEL_PDC_TNPR		0x118	/* Transmit Next Pointer Register */
#define ATMEL_PDC_TNCR		0x11c	/* Transmit Next Counter Register */

#define ATMEL_PDC_PTCR		0x120	/* Transfer Control Register */
#define		ATMEL_PDC_RXTEN		(1 << 0)	/* Receiver Transfer Enable */
#define		ATMEL_PDC_RXTDIS	(1 << 1)	/* Receiver Transfer Disable */
#define		ATMEL_PDC_TXTEN		(1 << 8)	/* Transmitter Transfer Enable */
#define		ATMEL_PDC_TXTDIS	(1 << 9)	/* Transmitter Transfer Disable */

#define ATMEL_PDC_PTSR		0x124	/* Transfer Status Register */

#define ATMEL_PDC_SCND_BUF_OFF	0x10	/* Offset between first and second buffer registers */

#endif
