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
#ifndef __I2400M_USB_H__
#define __I2400M_USB_H__

#include "i2400m.h"
#include <beep/kthread.h>


/*
 * Error Density Count: cheapo error density (over time) counter
 *
 * Originally by Reinette Chatre <reinette.chatre@intel.com>
 *
 * Embed an 'struct edc' somewhere. Each time there is a soft or
 * retryable error, call edc_inc() and check if the error top
 * watermark has been reached.
 */
enum {
	EDC_MAX_ERRORS = 10,
	EDC_ERROR_TIMEFRAME = HZ,
};

/* error density counter */
struct edc {
	unsigned long timestart;
	u16 errorcount;
};

struct i2400m_endpoint_cfg {
	unsigned char bulk_out;
	unsigned char notification;
	unsigned char reset_cold;
	unsigned char bulk_in;
};

static inline void edc_init(struct edc *edc)
{
	edc->timestart = jiffies;
}

/**
 * edc_inc - report a soft error and check if we are over the watermark
 *
 * @edc: pointer to error density counter.
 * @max_err: maximum number of errors we can accept over the timeframe
 * @timeframe: length of the timeframe (in jiffies).
 *
 * Returns: !0 1 if maximum acceptable errors per timeframe has been
 *     exceeded. 0 otherwise.
 *
 * This is way to determine if the number of acceptable errors per time
 * period has been exceeded. It is not accurate as there are cases in which
 * this scheme will not work, for example if there are periodic occurrences
 * of errors that straddle updates to the start time. This scheme is
 * sufficient for our usage.
 *
 * To use, embed a 'struct edc' somewhere, initialize it with
 * edc_init() and when an error hits:
 *
 * if (do_something_fails_with_a_soft_error) {
 *        if (edc_inc(&my->edc, MAX_ERRORS, MAX_TIMEFRAME))
 * 	           Ops, hard error, do something about it
 *        else
 *                 Retry or ignore, depending on whatever
 * }
 */
static inline int edc_inc(struct edc *edc, u16 max_err, u16 timeframe)
{
	unsigned long now;

	now = jiffies;
	if (now - edc->timestart > timeframe) {
		edc->errorcount = 1;
		edc->timestart = now;
	} else if (++edc->errorcount > max_err) {
		edc->errorcount = 0;
		edc->timestart = now;
		return 1;
	}
	return 0;
}

/* Host-Device interface for USB */
enum {
	I2400M_USB_BOOT_RETRIES = 3,
	I2400MU_MAX_NOTIFICATION_LEN = 256,
	I2400MU_BLK_SIZE = 16,
	I2400MU_PL_SIZE_MAX = 0x3EFF,

	/* Device IDs */
	USB_DEVICE_ID_I6050 = 0x0186,
	USB_DEVICE_ID_I6050_2 = 0x0188,
	USB_DEVICE_ID_I6150 = 0x07d6,
	USB_DEVICE_ID_I6150_2 = 0x07d7,
	USB_DEVICE_ID_I6150_3 = 0x07d9,
	USB_DEVICE_ID_I6250 = 0x0187,
};


/**
 * struct i2400mu - descriptor for a USB connected i2400m
 *
 * @i2400m: bus-generic i2400m implementation; has to be first (see
 *     it's documentation in i2400m.h).
 *
 * @usb_dev: pointer to our USB device
 *
 * @usb_iface: pointer to our USB interface
 *
 * @urb_edc: error density counter; used to keep a density-on-time tab
 *     on how many soft (retryable or ignorable) errors we get. If we
 *     go over the threshold, we consider the bus transport is failing
 *     too much and reset.
 *
 * @notif_urb: URB for receiving notifications from the device.
 *
 * @tx_kthread: thread we use for data TX. We use a thread because in
 *     order to do deep power saving and put the device to sleep, we
 *     need to call usb_autopm_*() [blocking functions].
 *
 * @tx_wq: waitqueue for the TX kthread to sleep when there is no data
 *     to be sent; when more data is available, it is woken up by
 *     i2400mu_bus_tx_kick().
 *
 * @rx_kthread: thread we use for data RX. We use a thread because in
 *     order to do deep power saving and put the device to sleep, we
 *     need to call usb_autopm_*() [blocking functions].
 *
 * @rx_wq: waitqueue for the RX kthread to sleep when there is no data
 *     to receive. When data is available, it is woken up by
 *     usb-notif.c:i2400mu_notification_grok().
 *
 * @rx_pending_count: number of rx-data-ready notifications that were
 *     still not handled by the RX kthread.
 *
 * @rx_size: current RX buffer size that is being used.
 *
 * @rx_size_acc: accumulator of the sizes of the previous read
 *     transactions.
 *
 * @rx_size_cnt: number of read transactions accumulated in
 *     @rx_size_acc.
 *
 * @do_autopm: disable(0)/enable(>0) calling the
 *     usb_autopm_get/put_interface() barriers when executing
 *     commands. See doc in i2400mu_suspend() for more information.
 *
 * @rx_size_auto_shrink: if true, the rx_size is shrunk
 *     automatically based on the average size of the received
 *     transactions. This allows the receive code to allocate smaller
 *     chunks of memory and thus reduce pressure on the memory
 *     allocator by not wasting so much space. By default it is
 *     enabled.
 *
 * @debugfs_dentry: hookup for debugfs files.
 *     These have to be in a separate directory, a child of
 *     (wimax_dev->debugfs_dentry) so they can be removed when the
 *     module unloads, as we don't keep each dentry.
 */
struct i2400mu {
	struct i2400m i2400m;		/* FIRST! See doc */

	struct usb_device *usb_dev;
	struct usb_interface *usb_iface;
	struct edc urb_edc;		/* Error density counter */
	struct i2400m_endpoint_cfg endpoint_cfg;

	struct urb *notif_urb;
	struct task_struct *tx_kthread;
	wait_queue_head_t tx_wq;

	struct task_struct *rx_kthread;
	wait_queue_head_t rx_wq;
	atomic_t rx_pending_count;
	size_t rx_size, rx_size_acc, rx_size_cnt;
	atomic_t do_autopm;
	u8 rx_size_auto_shrink;

	struct dentry *debugfs_dentry;
	unsigned i6050:1;	/* 1 if this is a 6050 based SKU */
};


static inline
void i2400mu_init(struct i2400mu *i2400mu)
{
	i2400m_init(&i2400mu->i2400m);
	edc_init(&i2400mu->urb_edc);
	init_waitqueue_head(&i2400mu->tx_wq);
	atomic_set(&i2400mu->rx_pending_count, 0);
	init_waitqueue_head(&i2400mu->rx_wq);
	i2400mu->rx_size = PAGE_SIZE - sizeof(struct skb_shared_info);
	atomic_set(&i2400mu->do_autopm, 1);
	i2400mu->rx_size_auto_shrink = 1;
}

extern int i2400mu_notification_setup(struct i2400mu *);
extern void i2400mu_notification_release(struct i2400mu *);

extern int i2400mu_rx_setup(struct i2400mu *);
extern void i2400mu_rx_release(struct i2400mu *);
extern void i2400mu_rx_kick(struct i2400mu *);

extern int i2400mu_tx_setup(struct i2400mu *);
extern void i2400mu_tx_release(struct i2400mu *);
extern void i2400mu_bus_tx_kick(struct i2400m *);

extern ssize_t i2400mu_bus_bm_cmd_send(struct i2400m *,
				       const struct i2400m_bootrom_header *,
				       size_t, int);
extern ssize_t i2400mu_bus_bm_wait_for_ack(struct i2400m *,
					   struct i2400m_bootrom_header *,
					   size_t);
#endif /* #ifndef __I2400M_USB_H__ */
