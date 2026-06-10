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
#ifndef	_SCC_H
#define	_SCC_H

#include <uapi/beep/scc.h>


enum {TX_OFF, TX_ON};	/* command for scc_key_trx() */

/* Vector masks in RR2B */

#define VECTOR_MASK	0x06
#define TXINT		0x00
#define EXINT		0x02
#define RXINT		0x04
#define SPINT		0x06

#ifdef CONFIG_SCC_DELAY
#define Inb(port)	inb_p(port)
#define Outb(port, val)	outb_p(val, port)
#else
#define Inb(port)	inb(port)
#define Outb(port, val)	outb(val, port)
#endif

/* SCC channel control structure for KISS */

struct scc_kiss {
	unsigned char txdelay;		/* Transmit Delay 10 ms/cnt */
	unsigned char persist;		/* Persistence (0-255) as a % */
	unsigned char slottime;		/* Delay to wait on persistence hit */
	unsigned char tailtime;		/* Delay after last byte written */
	unsigned char fulldup;		/* Full Duplex mode 0=CSMA 1=DUP 2=ALWAYS KEYED */
	unsigned char waittime;		/* Waittime before any transmit attempt */
	unsigned int  maxkeyup;		/* Maximum time to transmit (seconds) */
	unsigned int  mintime;		/* Minimal offtime after MAXKEYUP timeout (seconds) */
	unsigned int  idletime;		/* Maximum idle time in ALWAYS KEYED mode (seconds) */
	unsigned int  maxdefer;		/* Timer for CSMA channel busy limit */
	unsigned char tx_inhibit;	/* Transmit is not allowed when set */	
	unsigned char group;		/* Group ID for AX.25 TX interlocking */
	unsigned char mode;		/* 'normal' or 'hwctrl' mode (unused) */
	unsigned char softdcd;		/* Use DPLL instead of DCD pin for carrier detect */
};


/* SCC channel structure */

struct scc_channel {
	int init;			/* channel exists? */

	struct net_device *dev;		/* link to device control structure */
	struct net_device_stats dev_stat;/* device statistics */

	char brand;			/* manufacturer of the board */
	long clock;			/* used clock */

	io_port ctrl;			/* I/O address of CONTROL register */
	io_port	data;			/* I/O address of DATA register */
	io_port special;		/* I/O address of special function port */
	int irq;			/* Number of Interrupt */

	char option;
	char enhanced;			/* Enhanced SCC support */

	unsigned char wreg[16]; 	/* Copy of last written value in WRx */
	unsigned char status;		/* Copy of R0 at last external interrupt */
	unsigned char dcd;		/* DCD status */

        struct scc_kiss kiss;		/* control structure for KISS params */
        struct scc_stat stat;		/* statistical information */
        struct scc_modem modem; 	/* modem information */

        struct sk_buff_head tx_queue;	/* next tx buffer */
        struct sk_buff *rx_buff;	/* pointer to frame currently received */
        struct sk_buff *tx_buff;	/* pointer to frame currently transmitted */

	/* Timer */
	struct timer_list tx_t;		/* tx timer for this channel */
	struct timer_list tx_wdog;	/* tx watchdogs */
	
	/* Channel lock */
	spinlock_t	lock;		/* Channel guard lock */
};

#endif /* defined(_SCC_H) */
