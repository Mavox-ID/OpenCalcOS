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
#include <beep/module.h>
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/netdevice.h>
#include <beep/skbuff.h>
#include <net/pkt_sched.h>

/*
 * State of the queue, when used for network output buffering:
 *
 *                 plug(i+1)            plug(i)          head
 * ------------------+--------------------+---------------->
 *                   |                    |
 *                   |                    |
 * pkts_current_epoch| pkts_last_epoch    |pkts_to_release
 * ----------------->|<--------+--------->|+--------------->
 *                   v                    v
 *
 */

struct plug_sched_data {
	/* If true, the dequeue function releases all packets
	 * from head to end of the queue. The queue turns into
	 * a pass-through queue for newly arriving packets.
	 */
	bool unplug_indefinite;

	/* Queue Limit in bytes */
	u32 limit;

	/* Number of packets (output) from the current speculatively
	 * executing epoch.
	 */
	u32 pkts_current_epoch;

	/* Number of packets corresponding to the recently finished
	 * epoch. These will be released when we receive a
	 * TCQ_PLUG_RELEASE_ONE command. This command is typically
	 * issued after committing a checkpoint at the target.
	 */
	u32 pkts_last_epoch;

	/*
	 * Number of packets from the head of the queue, that can
	 * be released (committed checkpoint).
	 */
	u32 pkts_to_release;
};

static int plug_enqueue(struct sk_buff *skb, struct Qdisc *sch)
{
	struct plug_sched_data *q = qdisc_priv(sch);

	if (likely(sch->qstats.backlog + skb->len <= q->limit)) {
		if (!q->unplug_indefinite)
			q->pkts_current_epoch++;
		return qdisc_enqueue_tail(skb, sch);
	}

	return qdisc_reshape_fail(skb, sch);
}

static struct sk_buff *plug_dequeue(struct Qdisc *sch)
{
	struct plug_sched_data *q = qdisc_priv(sch);

	if (qdisc_is_throttled(sch))
		return NULL;

	if (!q->unplug_indefinite) {
		if (!q->pkts_to_release) {
			/* No more packets to dequeue. Block the queue
			 * and wait for the next release command.
			 */
			qdisc_throttled(sch);
			return NULL;
		}
		q->pkts_to_release--;
	}

	return qdisc_dequeue_head(sch);
}

static int plug_init(struct Qdisc *sch, struct nlattr *opt)
{
	struct plug_sched_data *q = qdisc_priv(sch);

	q->pkts_current_epoch = 0;
	q->pkts_last_epoch = 0;
	q->pkts_to_release = 0;
	q->unplug_indefinite = false;

	if (opt == NULL) {
		/* We will set a default limit of 100 pkts (~150kB)
		 * in case tx_queue_len is not available. The
		 * default value is completely arbitrary.
		 */
		u32 pkt_limit = qdisc_dev(sch)->tx_queue_len ? : 100;
		q->limit = pkt_limit * psched_mtu(qdisc_dev(sch));
	} else {
		struct tc_plug_qopt *ctl = nla_data(opt);

		if (nla_len(opt) < sizeof(*ctl))
			return -EINVAL;

		q->limit = ctl->limit;
	}

	qdisc_throttled(sch);
	return 0;
}

/* Receives 4 types of messages:
 * TCQ_PLUG_BUFFER: Inset a plug into the queue and
 *  buffer any incoming packets
 * TCQ_PLUG_RELEASE_ONE: Dequeue packets from queue head
 *   to beginning of the next plug.
 * TCQ_PLUG_RELEASE_INDEFINITE: Dequeue all packets from queue.
 *   Stop buffering packets until the next TCQ_PLUG_BUFFER
 *   command is received (just act as a pass-thru queue).
 * TCQ_PLUG_LIMIT: Increase/decrease queue size
 */
static int plug_change(struct Qdisc *sch, struct nlattr *opt)
{
	struct plug_sched_data *q = qdisc_priv(sch);
	struct tc_plug_qopt *msg;

	if (opt == NULL)
		return -EINVAL;

	msg = nla_data(opt);
	if (nla_len(opt) < sizeof(*msg))
		return -EINVAL;

	switch (msg->action) {
	case TCQ_PLUG_BUFFER:
		/* Save size of the current buffer */
		q->pkts_last_epoch = q->pkts_current_epoch;
		q->pkts_current_epoch = 0;
		if (q->unplug_indefinite)
			qdisc_throttled(sch);
		q->unplug_indefinite = false;
		break;
	case TCQ_PLUG_RELEASE_ONE:
		/* Add packets from the last complete buffer to the
		 * packets to be released set.
		 */
		q->pkts_to_release += q->pkts_last_epoch;
		q->pkts_last_epoch = 0;
		qdisc_unthrottled(sch);
		netif_schedule_queue(sch->dev_queue);
		break;
	case TCQ_PLUG_RELEASE_INDEFINITE:
		q->unplug_indefinite = true;
		q->pkts_to_release = 0;
		q->pkts_last_epoch = 0;
		q->pkts_current_epoch = 0;
		qdisc_unthrottled(sch);
		netif_schedule_queue(sch->dev_queue);
		break;
	case TCQ_PLUG_LIMIT:
		/* Limit is supplied in bytes */
		q->limit = msg->limit;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static struct Qdisc_ops plug_qdisc_ops __read_mostly = {
	.id          =       "plug",
	.priv_size   =       sizeof(struct plug_sched_data),
	.enqueue     =       plug_enqueue,
	.dequeue     =       plug_dequeue,
	.peek        =       qdisc_peek_head,
	.init        =       plug_init,
	.change      =       plug_change,
	.owner       =       THIS_MODULE,
};

static int __init plug_module_init(void)
{
	return register_qdisc(&plug_qdisc_ops);
}

static void __exit plug_module_exit(void)
{
	unregister_qdisc(&plug_qdisc_ops);
}
module_init(plug_module_init)
module_exit(plug_module_exit)
MODULE_LICENSE("GPL");
