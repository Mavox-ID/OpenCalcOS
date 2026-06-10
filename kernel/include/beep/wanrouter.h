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
#ifndef	_ROUTER_H
#define	_ROUTER_H

#include <uapi/beep/wanrouter.h>

/****** Kernel Interface ****************************************************/

#include <beep/fs.h>		/* support for device drivers */
#include <beep/proc_fs.h>	/* proc filesystem pragmatics */
#include <beep/netdevice.h>	/* support for network drivers */
#include <beep/spinlock.h>     /* Support for SMP Locking */

/*----------------------------------------------------------------------------
 * WAN device data space.
 */
struct wan_device {
	unsigned magic;			/* magic number */
	char* name;			/* -> WAN device name (ASCIIZ) */
	void* private;			/* -> driver private data */
	unsigned config_id;		/* Configuration ID */
					/****** hardware configuration ******/
	unsigned ioport;		/* adapter I/O port base #1 */
	char S514_cpu_no[1];		/* PCI CPU Number */
	unsigned char S514_slot_no;	/* PCI Slot Number */
	unsigned long maddr;		/* dual-port memory address */
	unsigned msize;			/* dual-port memory size */
	int irq;			/* interrupt request level */
	int dma;			/* DMA request level */
	unsigned bps;			/* data transfer rate */
	unsigned mtu;			/* max physical transmit unit size */
	unsigned udp_port;              /* UDP port for management */
        unsigned char ttl;		/* Time To Live for UDP security */
	unsigned enable_tx_int; 	/* Transmit Interrupt enabled or not */
	char interface;			/* RS-232/V.35, etc. */
	char clocking;			/* external/internal */
	char line_coding;		/* NRZ/NRZI/FM0/FM1, etc. */
	char station;			/* DTE/DCE, primary/secondary, etc. */
	char connection;		/* permanent/switched/on-demand */
	char signalling;		/* Signalling RS232 or V35 */
	char read_mode;			/* read mode: Polling or interrupt */
	char new_if_cnt;                /* Number of interfaces per wanpipe */ 
	char del_if_cnt;		/* Number of times del_if() gets called */
	unsigned char piggyback;        /* Piggibacking a port */
	unsigned hw_opt[4];		/* other hardware options */
					/****** status and statistics *******/
	char state;			/* device state */
	char api_status;		/* device api status */
	struct net_device_stats stats; 	/* interface statistics */
	unsigned reserved[16];		/* reserved for future use */
	unsigned long critical;		/* critical section flag */
	spinlock_t lock;                /* Support for SMP Locking */

					/****** device management methods ***/
	int (*setup) (struct wan_device *wandev, wandev_conf_t *conf);
	int (*shutdown) (struct wan_device *wandev);
	int (*update) (struct wan_device *wandev);
	int (*ioctl) (struct wan_device *wandev, unsigned cmd,
		unsigned long arg);
	int (*new_if)(struct wan_device *wandev, struct net_device *dev,
		      wanif_conf_t *conf);
	int (*del_if)(struct wan_device *wandev, struct net_device *dev);
					/****** maintained by the router ****/
	struct wan_device* next;	/* -> next device */
	struct net_device* dev;		/* list of network interfaces */
	unsigned ndev;			/* number of interfaces */
	struct proc_dir_entry *dent;	/* proc filesystem entry */
};

/* Public functions available for device drivers */
extern int register_wan_device(struct wan_device *wandev);
extern int unregister_wan_device(char *name);

/* Proc interface functions. These must not be called by the drivers! */
extern int wanrouter_proc_init(void);
extern void wanrouter_proc_cleanup(void);
extern int wanrouter_proc_add(struct wan_device *wandev);
extern int wanrouter_proc_delete(struct wan_device *wandev);
extern long wanrouter_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/* Public Data */
/* list of registered devices */
extern struct wan_device *wanrouter_router_devlist;

#endif	/* _ROUTER_H */
