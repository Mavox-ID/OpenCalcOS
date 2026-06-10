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
#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/init.h>

#include <asm/io.h>
#include <asm/processor.h>
#include <asm/intctl-regs.h>
#include <asm/rtc-regs.h>
#include <unit/leds.h>

#if 0
static const u8 asb2303_led_hex_tbl[16] = {
	0x80, 0xf2, 0x48, 0x60, 0x32, 0x24, 0x04, 0xf0,
	0x00, 0x20, 0x10, 0x06, 0x8c, 0x42, 0x0c, 0x1c
};
#endif

static const u8 asb2303_led_chase_tbl[6] = {
	~0x02,	/* top		- segA */
	~0x04,	/* right top	- segB */
	~0x08,	/* right bottom	- segC */
	~0x10,	/* bottom	- segD */
	~0x20,	/* left bottom	- segE */
	~0x40,	/* left top	- segF */
};

static unsigned asb2303_led_chase;

void peripheral_leds_display_exception(enum exception_code code)
{
	ASB2303_GPIO0DEF = 0x5555;	/* configure as an output port */
	ASB2303_7SEGLEDS = 0x6d;	/* triple horizontal bar */
}

void peripheral_leds_led_chase(void)
{
	ASB2303_GPIO0DEF = 0x5555;	/* configure as an output port */
	ASB2303_7SEGLEDS = asb2303_led_chase_tbl[asb2303_led_chase];
	asb2303_led_chase++;
	if (asb2303_led_chase >= 6)
		asb2303_led_chase = 0;
}
