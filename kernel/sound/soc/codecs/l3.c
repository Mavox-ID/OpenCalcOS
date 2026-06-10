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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/delay.h>

#include <sound/l3.h>

/*
 * Send one byte of data to the chip.  Data is latched into the chip on
 * the rising edge of the clock.
 */
static void sendbyte(struct l3_pins *adap, unsigned int byte)
{
	int i;

	for (i = 0; i < 8; i++) {
		adap->setclk(0);
		udelay(adap->data_hold);
		adap->setdat(byte & 1);
		udelay(adap->data_setup);
		adap->setclk(1);
		udelay(adap->clock_high);
		byte >>= 1;
	}
}

/*
 * Send a set of bytes to the chip.  We need to pulse the MODE line
 * between each byte, but never at the start nor at the end of the
 * transfer.
 */
static void sendbytes(struct l3_pins *adap, const u8 *buf,
		      int len)
{
	int i;

	for (i = 0; i < len; i++) {
		if (i) {
			udelay(adap->mode_hold);
			adap->setmode(0);
			udelay(adap->mode);
		}
		adap->setmode(1);
		udelay(adap->mode_setup);
		sendbyte(adap, buf[i]);
	}
}

int l3_write(struct l3_pins *adap, u8 addr, u8 *data, int len)
{
	adap->setclk(1);
	adap->setdat(1);
	adap->setmode(1);
	udelay(adap->mode);

	adap->setmode(0);
	udelay(adap->mode_setup);
	sendbyte(adap, addr);
	udelay(adap->mode_hold);

	sendbytes(adap, data, len);

	adap->setclk(1);
	adap->setdat(1);
	adap->setmode(0);

	return len;
}
EXPORT_SYMBOL_GPL(l3_write);

MODULE_DESCRIPTION("L3 bit-banging driver");
MODULE_AUTHOR("Christian Pellegrin <chripell@evolware.org>");
MODULE_LICENSE("GPL");
