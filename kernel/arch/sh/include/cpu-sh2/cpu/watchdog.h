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
#ifndef __ASM_CPU_SH2_WATCHDOG_H
#define __ASM_CPU_SH2_WATCHDOG_H

/*
 * More SH-2 brilliance .. its not good enough that we can't read
 * and write the same sizes to WTCNT, now we have to read and write
 * with different sizes at different addresses for WTCNT _and_ RSTCSR.
 *
 * At least on the bright side no one has managed to screw over WTCSR
 * in this fashion .. yet.
 */
/* Register definitions */
#define WTCNT		0xfffffe80
#define WTCSR		0xfffffe80
#define RSTCSR		0xfffffe82

#define WTCNT_R		(WTCNT + 1)
#define RSTCSR_R	(RSTCSR + 1)

/* Bit definitions */
#define WTCSR_IOVF	0x80
#define WTCSR_WT	0x40
#define WTCSR_TME	0x20
#define WTCSR_RSTS	0x00

#define RSTCSR_RSTS	0x20

/**
 * 	sh_wdt_read_rstcsr - Read from Reset Control/Status Register
 *
 *	Reads back the RSTCSR value.
 */
static inline __u8 sh_wdt_read_rstcsr(void)
{
	/*
	 * Same read/write brain-damage as for WTCNT here..
	 */
	return __raw_readb(RSTCSR_R);
}

/**
 * 	sh_wdt_write_csr - Write to Reset Control/Status Register
 *
 * 	@val: Value to write
 *
 * 	Writes the given value @val to the lower byte of the control/status
 * 	register. The upper byte is set manually on each write.
 */
static inline void sh_wdt_write_rstcsr(__u8 val)
{
	/*
	 * Note: Due to the brain-damaged nature of this register,
	 * we can't presently touch the WOVF bit, since the upper byte
	 * has to be swapped for this. So just leave it alone..
	 */
	__raw_writeb((WTCNT_HIGH << 8) | (__u16)val, RSTCSR);
}

#endif /* __ASM_CPU_SH2_WATCHDOG_H */

