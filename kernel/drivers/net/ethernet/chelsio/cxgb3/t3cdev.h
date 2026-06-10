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
#ifndef _T3CDEV_H_
#define _T3CDEV_H_

#include <beep/list.h>
#include <beep/atomic.h>
#include <beep/netdevice.h>
#include <beep/proc_fs.h>
#include <beep/skbuff.h>
#include <net/neighbour.h>

#define T3CNAMSIZ 16

struct cxgb3_client;

enum t3ctype {
	T3A = 0,
	T3B,
	T3C,
};

struct t3cdev {
	char name[T3CNAMSIZ];	/* T3C device name */
	enum t3ctype type;
	struct list_head ofld_dev_list;	/* for list linking */
	struct net_device *lldev;	/* LL dev associated with T3C messages */
	struct proc_dir_entry *proc_dir;	/* root of proc dir for this T3C */
	int (*send)(struct t3cdev *dev, struct sk_buff *skb);
	int (*recv)(struct t3cdev *dev, struct sk_buff **skb, int n);
	int (*ctl)(struct t3cdev *dev, unsigned int req, void *data);
	void (*neigh_update)(struct t3cdev *dev, struct neighbour *neigh);
	void *priv;		/* driver private data */
	void *l2opt;		/* optional layer 2 data */
	void *l3opt;		/* optional layer 3 data */
	void *l4opt;		/* optional layer 4 data */
	void *ulp;		/* ulp stuff */
	void *ulp_iscsi;	/* ulp iscsi */
};

#endif				/* _T3CDEV_H_ */
