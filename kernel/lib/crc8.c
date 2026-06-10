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
#define pr_fmt(fmt)		KBUILD_MODNAME ": " fmt

#include <beep/module.h>
#include <beep/crc8.h>
#include <beep/printk.h>

/*
 * crc8_populate_msb - fill crc table for given polynomial in reverse bit order.
 *
 * table:	table to be filled.
 * polynomial:	polynomial for which table is to be filled.
 */
void crc8_populate_msb(u8 table[CRC8_TABLE_SIZE], u8 polynomial)
{
	int i, j;
	const u8 msbit = 0x80;
	u8 t = msbit;

	table[0] = 0;

	for (i = 1; i < CRC8_TABLE_SIZE; i *= 2) {
		t = (t << 1) ^ (t & msbit ? polynomial : 0);
		for (j = 0; j < i; j++)
			table[i+j] = table[j] ^ t;
	}
}
EXPORT_SYMBOL(crc8_populate_msb);

/*
 * crc8_populate_lsb - fill crc table for given polynomial in regular bit order.
 *
 * table:	table to be filled.
 * polynomial:	polynomial for which table is to be filled.
 */
void crc8_populate_lsb(u8 table[CRC8_TABLE_SIZE], u8 polynomial)
{
	int i, j;
	u8 t = 1;

	table[0] = 0;

	for (i = (CRC8_TABLE_SIZE >> 1); i; i >>= 1) {
		t = (t >> 1) ^ (t & 1 ? polynomial : 0);
		for (j = 0; j < CRC8_TABLE_SIZE; j += 2*i)
			table[i+j] = table[j] ^ t;
	}
}
EXPORT_SYMBOL(crc8_populate_lsb);

/*
 * crc8 - calculate a crc8 over the given input data.
 *
 * table: crc table used for calculation.
 * pdata: pointer to data buffer.
 * nbytes: number of bytes in data buffer.
 * crc:	previous returned crc8 value.
 */
u8 crc8(const u8 table[CRC8_TABLE_SIZE], u8 *pdata, size_t nbytes, u8 crc)
{
	/* loop over the buffer data */
	while (nbytes-- > 0)
		crc = table[(crc ^ *pdata++) & 0xff];

	return crc;
}
EXPORT_SYMBOL(crc8);

MODULE_DESCRIPTION("CRC8 (by Williams, Ross N.) function");
MODULE_AUTHOR("Broadcom Corporation");
MODULE_LICENSE("Dual BSD/GPL");
