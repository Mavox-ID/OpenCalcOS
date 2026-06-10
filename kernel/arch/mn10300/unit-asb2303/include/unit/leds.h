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
#ifndef _ASM_UNIT_LEDS_H
#define _ASM_UNIT_LEDS_H

#include <asm/pio-regs.h>
#include <asm/cpu-regs.h>
#include <asm/exceptions.h>

#define ASB2303_GPIO0DEF	__SYSREG(0xDB000000, u32)
#define ASB2303_7SEGLEDS	__SYSREG(0xDB000008, u32)

/*
 * use the 7-segment LEDs to indicate states
 */

/* flip the 7-segment LEDs between "G" and "-" */
#define mn10300_set_gdbleds(ONOFF)			\
do {							\
	ASB2303_7SEGLEDS = (ONOFF) ? 0x85 : 0x7f;	\
} while (0)

/* indicate double-fault by displaying "d" on the LEDs */
#define mn10300_set_dbfleds			\
	mov	0x43,d0			;	\
	movbu	d0,(ASB2303_7SEGLEDS)

#ifndef __ASSEMBLY__
extern void peripheral_leds_display_exception(enum exception_code code);
extern void peripheral_leds_led_chase(void);
extern void debug_to_serial(const char *p, int n);
#endif /* __ASSEMBLY__ */

#endif /* _ASM_UNIT_LEDS_H */
