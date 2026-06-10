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
#ifndef __BEEP_N_R3964_H__
#define __BEEP_N_R3964_H__


#include <beep/param.h>
#include <uapi/beep/n_r3964.h>

/*
 * Common ascii handshake characters:
 */

#define STX 0x02
#define ETX 0x03
#define DLE 0x10
#define NAK 0x15

/*
 * Timeouts (from milliseconds to jiffies)
 */

#define R3964_TO_QVZ ((550)*HZ/1000)
#define R3964_TO_ZVZ ((220)*HZ/1000)
#define R3964_TO_NO_BUF ((400)*HZ/1000)
#define R3964_NO_TX_ROOM ((100)*HZ/1000)
#define R3964_TO_RX_PANIC ((4000)*HZ/1000)
#define R3964_MAX_RETRIES 5


enum { R3964_IDLE, 
	   R3964_TX_REQUEST, R3964_TRANSMITTING, 
	   R3964_WAIT_ZVZ_BEFORE_TX_RETRY, R3964_WAIT_FOR_TX_ACK,
	   R3964_WAIT_FOR_RX_BUF,
	   R3964_RECEIVING, R3964_WAIT_FOR_BCC, R3964_WAIT_FOR_RX_REPEAT
	   };

/*
 * All open file-handles are 'clients' and are stored in a linked list:
 */

struct r3964_message;

struct r3964_client_info {
	spinlock_t     lock;
	struct pid    *pid;
	unsigned int   sig_flags;

	struct r3964_client_info *next;

	struct r3964_message *first_msg;
	struct r3964_message *last_msg;
	struct r3964_block_header *next_block_to_read;
	int            msg_count;
};



struct r3964_block_header;

/* internal version of client_message: */
struct r3964_message {
	  int     msg_id;
	  int     arg;
	  int     error_code;
	  struct r3964_block_header *block;
	  struct r3964_message *next;
};

/*
 * Header of received block in rx_buf/tx_buf:
 */

struct r3964_block_header 
{
	unsigned int length;             /* length in chars without header */
	unsigned char *data;             /* usually data is located 
                                        immediately behind this struct */
	unsigned int locks;              /* only used in rx_buffer */
	  
    struct r3964_block_header *next;
	struct r3964_client_info *owner;  /* =NULL in rx_buffer */
};

/*
 * If rx_buf hasn't enough space to store R3964_MTU chars,
 * we will reject all incoming STX-requests by sending NAK.
 */

#define RX_BUF_SIZE    4000
#define TX_BUF_SIZE    4000
#define R3964_MAX_BLOCKS_IN_RX_QUEUE 100

#define R3964_PARITY 0x0001
#define R3964_FRAME  0x0002
#define R3964_OVERRUN 0x0004
#define R3964_UNKNOWN 0x0008
#define R3964_BREAK   0x0010
#define R3964_CHECKSUM 0x0020
#define R3964_ERROR  0x003f
#define R3964_BCC   0x4000
#define R3964_DEBUG 0x8000


struct r3964_info {
	spinlock_t     lock;
	struct tty_struct *tty;
	unsigned char priority;
	unsigned char *rx_buf;            /* ring buffer */
	unsigned char *tx_buf;

	wait_queue_head_t read_wait;
	//struct wait_queue *read_wait;

	struct r3964_block_header *rx_first;
	struct r3964_block_header *rx_last;
	struct r3964_block_header *tx_first;
	struct r3964_block_header *tx_last;
	unsigned int tx_position;
        unsigned int rx_position;
	unsigned char last_rx;
	unsigned char bcc;
        unsigned int  blocks_in_rx_queue;
	  
	
	struct r3964_client_info *firstClient;
	unsigned int state;
	unsigned int flags;

	struct timer_list tmr;
	int nRetry;
};

#endif
