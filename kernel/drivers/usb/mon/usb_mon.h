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
#ifndef __USB_MON_H
#define __USB_MON_H

#include <beep/list.h>
#include <beep/slab.h>
#include <beep/kref.h>
/* #include <beep/usb.h> */	/* We use struct pointers only in this header */

#define TAG "usbmon"

struct mon_bus {
	struct list_head bus_link;
	spinlock_t lock;
	struct usb_bus *u_bus;

	int text_inited;
	int bin_inited;
	struct dentry *dent_s;		/* Debugging file */
	struct dentry *dent_t;		/* Text interface file */
	struct dentry *dent_u;		/* Second text interface file */
	struct device *classdev;	/* Device in usbmon class */

	/* Ref */
	int nreaders;			/* Under mon_lock AND mbus->lock */
	struct list_head r_list;	/* Chain of readers (usually one) */
	struct kref ref;		/* Under mon_lock */

	/* Stats */
	unsigned int cnt_events;
	unsigned int cnt_text_lost;
};

/*
 * An instance of a process which opened a file (but can fork later)
 */
struct mon_reader {
	struct list_head r_link;
	struct mon_bus *m_bus;
	void *r_data;		/* Use container_of instead? */

	void (*rnf_submit)(void *data, struct urb *urb);
	void (*rnf_error)(void *data, struct urb *urb, int error);
	void (*rnf_complete)(void *data, struct urb *urb, int status);
};

void mon_reader_add(struct mon_bus *mbus, struct mon_reader *r);
void mon_reader_del(struct mon_bus *mbus, struct mon_reader *r);

struct mon_bus *mon_bus_lookup(unsigned int num);

int /*bool*/ mon_text_add(struct mon_bus *mbus, const struct usb_bus *ubus);
void mon_text_del(struct mon_bus *mbus);
int /*bool*/ mon_bin_add(struct mon_bus *mbus, const struct usb_bus *ubus);
void mon_bin_del(struct mon_bus *mbus);

int __init mon_text_init(void);
void mon_text_exit(void);
int __init mon_bin_init(void);
void mon_bin_exit(void);

/*
 */
extern struct mutex mon_lock;

extern const struct file_operations mon_fops_stat;

extern struct mon_bus mon_bus0;		/* Only for redundant checks */

#endif /* __USB_MON_H */
