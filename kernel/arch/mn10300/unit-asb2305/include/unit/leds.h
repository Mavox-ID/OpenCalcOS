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

#define ASB2305_7SEGLEDS	__SYSREG(0xA6F90000, u32)

/* perform a hard reset by driving PIO06 low */
#define mn10300_unit_hard_reset()		\
do {						\
	P0OUT &= 0xbf;				\
	P0MD = (P0MD & P0MD_6) | P0MD_6_OUT;	\
} while (0)

/*
 * use the 7-segment LEDs to indicate states
 */
/* indicate double-fault by displaying "db-f" on the LEDs */
#define mn10300_set_dbfleds			\
	mov	0x43077f1d,d0		;	\
	mov	d0,(ASB2305_7SEGLEDS)

/* flip the 7-segment LEDs between "Gdb-" and "----" */
#define mn10300_set_gdbleds(ONOFF)				\
do {								\
	ASB2305_7SEGLEDS = (ONOFF) ? 0x8543077f : 0x7f7f7f7f;	\
} while (0)

#ifndef __ASSEMBLY__
extern void peripheral_leds_display_exception(enum exception_code);
extern void peripheral_leds_led_chase(void);
extern void peripheral_leds7x4_display_dec(unsigned int, unsigned int);
extern void peripheral_leds7x4_display_hex(unsigned int, unsigned int);
extern void peripheral_leds7x4_display_minssecs(unsigned int, unsigned int);
extern void peripheral_leds7x4_display_rtc(void);
#endif /* __ASSEMBLY__ */

#endif /* _ASM_UNIT_LEDS_H */
