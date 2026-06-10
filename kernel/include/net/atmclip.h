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
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
 
 
#ifndef _ATMCLIP_H
#define _ATMCLIP_H

#include <beep/netdevice.h>
#include <beep/atm.h>
#include <beep/atmdev.h>
#include <beep/atmarp.h>
#include <beep/spinlock.h>
#include <net/neighbour.h>


#define CLIP_VCC(vcc) ((struct clip_vcc *) ((vcc)->user_back))

struct sk_buff;

struct clip_vcc {
	struct atm_vcc	*vcc;		/* VCC descriptor */
	struct atmarp_entry *entry;	/* ATMARP table entry, NULL if IP addr.
					   isn't known yet */
	int		xoff;		/* 1 if send buffer is full */
	unsigned char	encap;		/* 0: NULL, 1: LLC/SNAP */
	unsigned long	last_use;	/* last send or receive operation */
	unsigned long	idle_timeout;	/* keep open idle for so many jiffies*/
	void (*old_push)(struct atm_vcc *vcc,struct sk_buff *skb);
					/* keep old push fn for chaining */
	void (*old_pop)(struct atm_vcc *vcc,struct sk_buff *skb);
					/* keep old pop fn for chaining */
	struct clip_vcc	*next;		/* next VCC */
};


struct atmarp_entry {
	struct clip_vcc	*vccs;		/* active VCCs; NULL if resolution is
					   pending */
	unsigned long	expires;	/* entry expiration time */
	struct neighbour *neigh;	/* neighbour back-pointer */
};

#define PRIV(dev) ((struct clip_priv *) netdev_priv(dev))

struct clip_priv {
	int number;			/* for convenience ... */
	spinlock_t xoff_lock;		/* ensures that pop is atomic (SMP) */
	struct net_device *next;	/* next CLIP interface */
};

#endif
