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
#ifndef __ASM_CPU_SH4_WATCHDOG_H
#define __ASM_CPU_SH4_WATCHDOG_H

#if defined(CONFIG_CPU_SUBTYPE_SH7785) || defined(CONFIG_CPU_SUBTYPE_SH7780)
/* Prefix definition */
#define WTBST_HIGH	0x55
/* Register definitions */
#define WTCNT_R		0xffcc0010 /*WDTCNT*/
#define WTCSR		0xffcc0004 /*WDTCSR*/
#define WTCNT		0xffcc0000 /*WDTST*/
#define WTST		WTCNT
#define WTBST		0xffcc0008 /*WDTBST*/
/* Register definitions */
#elif	defined(CONFIG_CPU_SUBTYPE_SH7722) || \
	defined(CONFIG_CPU_SUBTYPE_SH7723) || \
	defined(CONFIG_CPU_SUBTYPE_SH7724)
#define WTCNT		0xa4520000
#define WTCSR		0xa4520004
#else
/* Register definitions */
#define WTCNT		0xffc00008
#define WTCSR		0xffc0000c
#endif

/* Bit definitions */
#define WTCSR_TME	0x80
#define WTCSR_WT	0x40
#define WTCSR_RSTS	0x20
#define WTCSR_WOVF	0x10
#define WTCSR_IOVF	0x08

#endif /* __ASM_CPU_SH4_WATCHDOG_H */

