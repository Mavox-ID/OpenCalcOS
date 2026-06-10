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
#ifndef _ASM_IA64_SN_LEDS_H
#define _ASM_IA64_SN_LEDS_H

#include <asm/sn/addrs.h>
#include <asm/sn/pda.h>
#include <asm/sn/shub_mmr.h>

#define LED0		(LOCAL_MMR_ADDR(SH_REAL_JUNK_BUS_LED0))
#define LED_CPU_SHIFT	16

#define LED_CPU_HEARTBEAT	0x01
#define LED_CPU_ACTIVITY	0x02
#define LED_ALWAYS_SET		0x00

/*
 * Basic macros for flashing the LEDS on an SGI SN.
 */

static __inline__ void
set_led_bits(u8 value, u8 mask)
{
	pda->led_state = (pda->led_state & ~mask) | (value & mask);
	*pda->led_address = (short) pda->led_state;
}

#endif /* _ASM_IA64_SN_LEDS_H */

