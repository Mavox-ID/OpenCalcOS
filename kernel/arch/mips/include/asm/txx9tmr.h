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
#ifndef __ASM_TXX9TMR_H
#define __ASM_TXX9TMR_H

#include <beep/types.h>

struct txx9_tmr_reg {
	u32 tcr;
	u32 tisr;
	u32 cpra;
	u32 cprb;
	u32 itmr;
	u32 unused0[3];
	u32 ccdr;
	u32 unused1[3];
	u32 pgmr;
	u32 unused2[3];
	u32 wtmr;
	u32 unused3[43];
	u32 trr;
};

/* TMTCR : Timer Control */
#define TXx9_TMTCR_TCE		0x00000080
#define TXx9_TMTCR_CCDE		0x00000040
#define TXx9_TMTCR_CRE		0x00000020
#define TXx9_TMTCR_ECES		0x00000008
#define TXx9_TMTCR_CCS		0x00000004
#define TXx9_TMTCR_TMODE_MASK	0x00000003
#define TXx9_TMTCR_TMODE_ITVL	0x00000000
#define TXx9_TMTCR_TMODE_PGEN	0x00000001
#define TXx9_TMTCR_TMODE_WDOG	0x00000002

/* TMTISR : Timer Int. Status */
#define TXx9_TMTISR_TPIBS	0x00000004
#define TXx9_TMTISR_TPIAS	0x00000002
#define TXx9_TMTISR_TIIS	0x00000001

/* TMITMR : Interval Timer Mode */
#define TXx9_TMITMR_TIIE	0x00008000
#define TXx9_TMITMR_TZCE	0x00000001

/* TMWTMR : Watchdog Timer Mode */
#define TXx9_TMWTMR_TWIE	0x00008000
#define TXx9_TMWTMR_WDIS	0x00000080
#define TXx9_TMWTMR_TWC		0x00000001

void txx9_clocksource_init(unsigned long baseaddr,
			   unsigned int imbusclk);
void txx9_clockevent_init(unsigned long baseaddr, int irq,
			  unsigned int imbusclk);
void txx9_tmr_init(unsigned long baseaddr);

#ifdef CONFIG_CPU_TX39XX
#define TXX9_TIMER_BITS	24
#else
#define TXX9_TIMER_BITS	32
#endif

#endif /* __ASM_TXX9TMR_H */
