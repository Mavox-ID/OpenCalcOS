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
#ifndef CARD_H
#define CARD_H

/*
 * We need these if they're not already included
 */
#include <beep/timer.h>
#include <beep/time.h>
#include <beep/isdnif.h>
#include <beep/irqreturn.h>
#include "message.h"
#include "scioc.h"

/*
 * Amount of time to wait for a reset to complete
 */
#define CHECKRESET_TIME		msecs_to_jiffies(4000)

/*
 * Amount of time between line status checks
 */
#define CHECKSTAT_TIME		msecs_to_jiffies(8000)

/*
 * The maximum amount of time to wait for a message response
 * to arrive. Use exclusively by send_and_receive
 */
#define SAR_TIMEOUT		msecs_to_jiffies(10000)

/*
 * Macro to determine is a card id is valid
 */
#define IS_VALID_CARD(x)	((x >= 0) && (x <= cinst))

/*
 * Per channel status and configuration
 */
typedef struct {
	int l2_proto;
	int l3_proto;
	char dn[50];
	unsigned long first_sendbuf;	/* Offset of first send buffer */
	unsigned int num_sendbufs;	/* Number of send buffers */
	unsigned int free_sendbufs;	/* Number of free sendbufs */
	unsigned int next_sendbuf;	/* Next sequential buffer */
	char eazlist[50];		/* Set with SETEAZ */
	char sillist[50];		/* Set with SETSIL */
	int eazclear;			/* Don't accept calls if TRUE */
} bchan;

/*
 * Everything you want to know about the adapter ...
 */
typedef struct {
	int model;
	int driverId;			/* LL Id */
	char devicename[20];		/* The device name */
	isdn_if *card;			/* ISDN4Beep structure */
	bchan *channel;			/* status of the B channels */
	char nChannels;			/* Number of channels */
	unsigned int interrupt;		/* Interrupt number */
	int iobase;			/* I/O Base address */
	int ioport[MAX_IO_REGS];	/* Index to I/O ports */
	int shmem_pgport;		/* port for the exp mem page reg. */
	int shmem_magic;		/* adapter magic number */
	unsigned int rambase;		/* Shared RAM base address */
	unsigned int ramsize;		/* Size of shared memory */
	RspMessage async_msg;		/* Async response message */
	int want_async_messages;	/* Snoop the Q ? */
	unsigned char seq_no;		/* Next send seq. number */
	struct timer_list reset_timer;	/* Check reset timer */
	struct timer_list stat_timer;	/* Check startproc timer */
	unsigned char nphystat;		/* Latest PhyStat info */
	unsigned char phystat;		/* Last PhyStat info */
	HWConfig_pl hwconfig;		/* Hardware config info */
	char load_ver[11];		/* CommManage Version string */
	char proc_ver[11];		/* CommEngine Version */
	int StartOnReset;		/* Indicates startproc after reset */
	int EngineUp;			/* Indicates CommEngine Up */
	int trace_mode;			/* Indicate if tracing is on */
	spinlock_t lock;		/* local lock */
} board;


extern board *sc_adapter[];
extern int cinst;

void memcpy_toshmem(int card, void *dest, const void *src, size_t n);
void memcpy_fromshmem(int card, void *dest, const void *src, size_t n);
int get_card_from_id(int driver);
int indicate_status(int card, int event, ulong Channel, char *Data);
irqreturn_t interrupt_handler(int interrupt, void *cardptr);
int sndpkt(int devId, int channel, int ack, struct sk_buff *data);
void rcvpkt(int card, RspMessage *rcvmsg);
int command(isdn_ctrl *cmd);
int reset(int card);
int startproc(int card);
int send_and_receive(int card, unsigned int procid, unsigned char type,
		     unsigned char class, unsigned char code,
		     unsigned char link, unsigned char data_len,
		     unsigned char *data,  RspMessage *mesgdata, int timeout);
void flushreadfifo(int card);
int sendmessage(int card, unsigned int procid, unsigned int type,
		unsigned int class, unsigned int code, unsigned int link,
		unsigned int data_len, unsigned int *data);
int receivemessage(int card, RspMessage *rspmsg);
int sc_ioctl(int card, scs_ioctl *data);
int setup_buffers(int card, int c);
void sc_check_reset(unsigned long data);
void check_phystat(unsigned long data);

#endif /* CARD_H */
