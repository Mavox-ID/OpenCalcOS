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
/* Registers */
#define HPLANCE_ID		0x01		/* DIO register: ID byte */
#define HPLANCE_STATUS		0x03		/* DIO register: interrupt enable/status */

/* Control and status bits for the status register */
#define LE_IE 0x80                                /* interrupt enable */
#define LE_IR 0x40                                /* interrupt requested */
#define LE_LOCK 0x08                              /* lock status register */
#define LE_ACK 0x04                               /* ack of lock */
#define LE_JAB 0x02                               /* loss of tx clock (???) */
/* We can also extract the IPL from the status register with the standard
 * DIO_IPL(hplance) macro, or using dio_scodetoipl()
 */

/* These are the offsets for the DIO regs (hplance_reg), lance_ioreg,
 * memory and NVRAM:
 */
#define HPLANCE_IDOFF 0                           /* board baseaddr */
#define HPLANCE_REGOFF 0x4000                     /* lance registers */
#define HPLANCE_MEMOFF 0x8000                     /* struct lance_init_block */
#define HPLANCE_NVRAMOFF 0xC008                   /* etheraddress as one *nibble* per byte */
