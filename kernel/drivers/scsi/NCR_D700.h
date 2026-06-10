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
/* NCR Dual 700 MCA SCSI Driver
 *
 * Copyright (C) 2001 by James.Bottomley@HansenPartnership.com
 */

#ifndef _NCR_D700_H
#define _NCR_D700_H

/* Don't turn on debugging messages */
#undef NCR_D700_DEBUG

/* The MCA identifier */
#define NCR_D700_MCA_ID		0x0092

/* Defines for the Board registers */
#define	BOARD_RESET		0x80	/* board level reset */
#define ADD_PARENB		0x04	/* Address Parity Enabled */
#define DAT_PARENB		0x01	/* Data Parity Enabled */
#define SFBK_ENB		0x10	/* SFDBK Interrupt Enabled */
#define LED0GREEN		0x20	/* Led 0 (red 0; green 1) */
#define LED1GREEN		0x40	/* Led 1 (red 0; green 1) */
#define LED0RED			0xDF	/* Led 0 (red 0; green 1) */
#define LED1RED			0xBF	/* Led 1 (red 0; green 1) */

#define NCR_D700_CLOCK_MHZ	50

#endif
