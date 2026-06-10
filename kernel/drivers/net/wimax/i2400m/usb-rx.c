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
#include <beep/workqueue.h>
#include <beep/slab.h>
#include <beep/usb.h>
#include "i2400m-usb.h"


#define D_SUBMODULE rx
#include "usb-debug-levels.h"

/*
 * Dynamic RX size
 *
 * We can't let the rx_size be a multiple of 512 bytes (the RX
 * endpoint's max packet size). On some USB host controllers (we
 * haven't been able to fully characterize which), if the device is
 * about to send (for example) X bytes and we only post a buffer to
 * receive n*512, it will fail to mark that as babble (so that
 * i2400mu_rx() [case -EOVERFLOW] can resize the buffer and get the
 * rest).
 *
 * So on growing or shrinking, if it is a multiple of the
 * maxpacketsize, we remove some (instead of incresing some, so in a
 * buddy allocator we try to waste less space).
 *
 * Note we also need a hook for this on i2400mu_rx() -- when we do the
 * first read, we are sure we won't hit this spot because
 * i240mm->rx_size has been set properly. However, if we have to
 * double because of -EOVERFLOW, when we launch the read to get the
 * rest of the data, we *have* to make sure that also is not a
 * multiple of the max_pkt_size.
 */

static
size_t i2400mu_rx_size_grow(struct i2400mu *i2400mu)
{
	struct device *dev = &i2400mu->usb_iface->dev;
	size_t rx_size;
	const size_t max_pkt_size = 512;

	rx_size = 2 * i2400mu->rx_size;
	if (rx_size % max_pkt_size == 0) {
		rx_size -= 8;
		d_printf(1, dev,
			 "RX: expected size grew to %zu [adjusted -8] "
			 "from %zu\n",
			 rx_size, i2400mu->rx_size);
	} else
		d_printf(1, dev,
			 "RX: expected size grew to %zu from %zu\n",
			 rx_size, i2400mu->rx_size);
	return rx_size;
}


static
void i2400mu_rx_size_maybe_shrink(struct i2400mu *i2400mu)
{
	const size_t max_pkt_size = 512;
	struct device *dev = &i2400mu->usb_iface->dev;

	if (unlikely(i2400mu->rx_size_cnt >= 100
		     && i2400mu->rx_size_auto_shrink)) {
		size_t avg_rx_size =
			i2400mu->rx_size_acc / i2400mu->rx_size_cnt;
		size_t new_rx_size = i2400mu->rx_size / 2;
		if (avg_rx_size < new_rx_size) {
			if (new_rx_size % max_pkt_size == 0) {
				new_rx_size -= 8;
				d_printf(1, dev,
					 "RX: expected size shrank to %zu "
					 "[adjusted -8] from %zu\n",
					 new_rx_size, i2400mu->rx_size);
			} else
				d_printf(1, dev,
					 "RX: expected size shrank to %zu "
					 "from %zu\n",
					 new_rx_size, i2400mu->rx_size);
			i2400mu->rx_size = new_rx_size;
			i2400mu->rx_size_cnt = 0;
			i2400mu->rx_size_acc = i2400mu->rx_size;
		}
	}
}

/*
 * Receive a message with payloads from the USB bus into an skb
 *
 * @i2400mu: USB device descriptor
 * @rx_skb: skb where to place the received message
 *
 * Deals with all the USB-specifics of receiving, dynamically
 * increasing the buffer size if so needed. Returns the payload in the
 * skb, ready to process. On a zero-length packet, we retry.
 *
 * On soft USB errors, we retry (until they become too frequent and
 * then are promoted to hard); on hard USB errors, we reset the
 * device. On other errors (skb realloacation, we just drop it and
 * hope for the next invocation to solve it).
 *
 * Returns: pointer to the skb if ok, ERR_PTR on error.
 *   NOTE: this function might realloc the skb (if it is too small),
 *   so always update with the one returned.
 *   ERR_PTR() is < 0 on error.
 *   Will return NULL if it cannot reallocate -- this can be
 *   considered a transient retryable error.
 */
static
struct sk_buff *i2400mu_rx(struct i2400mu *i2400mu, struct sk_buff *rx_skb)
{
	int result = 0;
	struct device *dev = &i2400mu->usb_iface->dev;
	int usb_pipe, read_size, rx_size, do_autopm;
	struct usb_endpoint_descriptor *epd;
	const size_t max_pkt_size = 512;

	d_fnstart(4, dev, "(i2400mu %p)\n", i2400mu);
	do_autopm = atomic_read(&i2400mu->do_autopm);
	result = do_autopm ?
		usb_autopm_get_interface(i2400mu->usb_iface) : 0;
	if (result < 0) {
		dev_err(dev, "RX: can't get autopm: %d\n", result);
		do_autopm = 0;
	}
	epd = usb_get_epd(i2400mu->usb_iface, i2400mu->endpoint_cfg.bulk_in);
	usb_pipe = usb_rcvbulkpipe(i2400mu->usb_dev, epd->bEndpointAddress);
retry:
	rx_size = skb_end_pointer(rx_skb) - rx_skb->data - rx_skb->len;
	if (unlikely(rx_size % max_pkt_size == 0)) {
		rx_size -= 8;
		d_printf(1, dev, "RX: rx_size adapted to %d [-8]\n", rx_size);
	}
	result = usb_bulk_msg(
		i2400mu->usb_dev, usb_pipe, rx_skb->data + rx_skb->len,
		rx_size, &read_size, 200);
	usb_mark_last_busy(i2400mu->usb_dev);
	switch (result) {
	case 0:
		if (read_size == 0)
			goto retry;	/* ZLP, just resubmit */
		skb_put(rx_skb, read_size);
		break;
	case -EPIPE:
		/*
		 * Stall -- maybe the device is choking with our
		 * requests. Clear it and give it some time. If they
		 * happen to often, it might be another symptom, so we
		 * reset.
		 *
		 * No error handling for usb_clear_halt(0; if it
		 * works, the retry works; if it fails, this switch
		 * does the error handling for us.
		 */
		if (edc_inc(&i2400mu->urb_edc,
			    10 * EDC_MAX_ERRORS, EDC_ERROR_TIMEFRAME)) {
			dev_err(dev, "BM-CMD: too many stalls in "
				"URB; resetting device\n");
			goto do_reset;
		}
		usb_clear_halt(i2400mu->usb_dev, usb_pipe);
		msleep(10);	/* give the device some time */
		goto retry;
	case -EINVAL:			/* while removing driver */
	case -ENODEV:			/* dev disconnect ... */
	case -ENOENT:			/* just ignore it */
	case -ESHUTDOWN:
	case -ECONNRESET:
		break;
	case -EOVERFLOW: {		/* too small, reallocate */
		struct sk_buff *new_skb;
		rx_size = i2400mu_rx_size_grow(i2400mu);
		if (rx_size <= (1 << 16))	/* cap it */
			i2400mu->rx_size = rx_size;
		else if (printk_ratelimit()) {
			dev_err(dev, "BUG? rx_size up to %d\n", rx_size);
			result = -EINVAL;
			goto out;
		}
		skb_put(rx_skb, read_size);
		new_skb = skb_copy_expand(rx_skb, 0, rx_size - rx_skb->len,
					  GFP_KERNEL);
		if (new_skb == NULL) {
			if (printk_ratelimit())
				dev_err(dev, "RX: Can't reallocate skb to %d; "
					"RX dropped\n", rx_size);
			kfree_skb(rx_skb);
			rx_skb = NULL;
			goto out;	/* drop it...*/
		}
		kfree_skb(rx_skb);
		rx_skb = new_skb;
		i2400mu->rx_size_cnt = 0;
		i2400mu->rx_size_acc = i2400mu->rx_size;
		d_printf(1, dev, "RX: size changed to %d, received %d, "
			 "copied %d, capacity %ld\n",
			 rx_size, read_size, rx_skb->len,
			 (long) skb_end_offset(new_skb));
		goto retry;
	}
		/* In most cases, it happens due to the hardware scheduling a
		 * read when there was no data - unfortunately, we have no way
		 * to tell this timeout from a USB timeout. So we just ignore
		 * it. */
	case -ETIMEDOUT:
		dev_err(dev, "RX: timeout: %d\n", result);
		result = 0;
		break;
	default:			/* Any error */
		if (edc_inc(&i2400mu->urb_edc,
			    EDC_MAX_ERRORS, EDC_ERROR_TIMEFRAME))
			goto error_reset;
		dev_err(dev, "RX: error receiving URB: %d, retrying\n", result);
		goto retry;
	}
out:
	if (do_autopm)
		usb_autopm_put_interface(i2400mu->usb_iface);
	d_fnend(4, dev, "(i2400mu %p) = %p\n", i2400mu, rx_skb);
	return rx_skb;

error_reset:
	dev_err(dev, "RX: maximum errors in URB exceeded; "
		"resetting device\n");
do_reset:
	usb_queue_reset_device(i2400mu->usb_iface);
	rx_skb = ERR_PTR(result);
	goto out;
}


/*
 * Kernel thread for USB reception of data
 *
 * This thread waits for a kick; once kicked, it will allocate an skb
 * and receive a single message to it from USB (using
 * i2400mu_rx()). Once received, it is passed to the generic i2400m RX
 * code for processing.
 *
 * When done processing, it runs some dirty statistics to verify if
 * the last 100 messages received were smaller than half of the
 * current RX buffer size. In that case, the RX buffer size is
 * halved. This will helps lowering the pressure on the memory
 * allocator.
 *
 * Hard errors force the thread to exit.
 */
static
int i2400mu_rxd(void *_i2400mu)
{
	int result = 0;
	struct i2400mu *i2400mu = _i2400mu;
	struct i2400m *i2400m = &i2400mu->i2400m;
	struct device *dev = &i2400mu->usb_iface->dev;
	struct net_device *net_dev = i2400m->wimax_dev.net_dev;
	size_t pending;
	int rx_size;
	struct sk_buff *rx_skb;
	unsigned long flags;

	d_fnstart(4, dev, "(i2400mu %p)\n", i2400mu);
	spin_lock_irqsave(&i2400m->rx_lock, flags);
	BUG_ON(i2400mu->rx_kthread != NULL);
	i2400mu->rx_kthread = current;
	spin_unlock_irqrestore(&i2400m->rx_lock, flags);
	while (1) {
		d_printf(2, dev, "RX: waiting for messages\n");
		pending = 0;
		wait_event_interruptible(
			i2400mu->rx_wq,
			(kthread_should_stop()	/* check this first! */
			 || (pending = atomic_read(&i2400mu->rx_pending_count)))
			);
		if (kthread_should_stop())
			break;
		if (pending == 0)
			continue;
		rx_size = i2400mu->rx_size;
		d_printf(2, dev, "RX: reading up to %d bytes\n", rx_size);
		rx_skb = __netdev_alloc_skb(net_dev, rx_size, GFP_KERNEL);
		if (rx_skb == NULL) {
			dev_err(dev, "RX: can't allocate skb [%d bytes]\n",
				rx_size);
			msleep(50);	/* give it some time? */
			continue;
		}

		/* Receive the message with the payloads */
		rx_skb = i2400mu_rx(i2400mu, rx_skb);
		result = PTR_ERR(rx_skb);
		if (IS_ERR(rx_skb))
			goto out;
		atomic_dec(&i2400mu->rx_pending_count);
		if (rx_skb == NULL || rx_skb->len == 0) {
			/* some "ignorable" condition */
			kfree_skb(rx_skb);
			continue;
		}

		/* Deliver the message to the generic i2400m code */
		i2400mu->rx_size_cnt++;
		i2400mu->rx_size_acc += rx_skb->len;
		result = i2400m_rx(i2400m, rx_skb);
		if (result == -EIO
		    && edc_inc(&i2400mu->urb_edc,
			       EDC_MAX_ERRORS, EDC_ERROR_TIMEFRAME)) {
			goto error_reset;
		}

		/* Maybe adjust RX buffer size */
		i2400mu_rx_size_maybe_shrink(i2400mu);
	}
	result = 0;
out:
	spin_lock_irqsave(&i2400m->rx_lock, flags);
	i2400mu->rx_kthread = NULL;
	spin_unlock_irqrestore(&i2400m->rx_lock, flags);
	d_fnend(4, dev, "(i2400mu %p) = %d\n", i2400mu, result);
	return result;

error_reset:
	dev_err(dev, "RX: maximum errors in received buffer exceeded; "
		"resetting device\n");
	usb_queue_reset_device(i2400mu->usb_iface);
	goto out;
}


/*
 * Start reading from the device
 *
 * @i2400m: device instance
 *
 * Notify the RX thread that there is data pending.
 */
void i2400mu_rx_kick(struct i2400mu *i2400mu)
{
	struct i2400m *i2400m = &i2400mu->i2400m;
	struct device *dev = &i2400mu->usb_iface->dev;

	d_fnstart(3, dev, "(i2400mu %p)\n", i2400m);
	atomic_inc(&i2400mu->rx_pending_count);
	wake_up_all(&i2400mu->rx_wq);
	d_fnend(3, dev, "(i2400m %p) = void\n", i2400m);
}


int i2400mu_rx_setup(struct i2400mu *i2400mu)
{
	int result = 0;
	struct i2400m *i2400m = &i2400mu->i2400m;
	struct device *dev = &i2400mu->usb_iface->dev;
	struct wimax_dev *wimax_dev = &i2400m->wimax_dev;
	struct task_struct *kthread;

	kthread = kthread_run(i2400mu_rxd, i2400mu, "%s-rx",
			      wimax_dev->name);
	/* the kthread function sets i2400mu->rx_thread */
	if (IS_ERR(kthread)) {
		result = PTR_ERR(kthread);
		dev_err(dev, "RX: cannot start thread: %d\n", result);
	}
	return result;
}


void i2400mu_rx_release(struct i2400mu *i2400mu)
{
	unsigned long flags;
	struct i2400m *i2400m = &i2400mu->i2400m;
	struct device *dev = i2400m_dev(i2400m);
	struct task_struct *kthread;

	spin_lock_irqsave(&i2400m->rx_lock, flags);
	kthread = i2400mu->rx_kthread;
	i2400mu->rx_kthread = NULL;
	spin_unlock_irqrestore(&i2400m->rx_lock, flags);
	if (kthread)
		kthread_stop(kthread);
	else
		d_printf(1, dev, "RX: kthread had already exited\n");
}

