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
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <beep/module.h>
#include <beep/slab.h>
#include <beep/spinlock.h>
#include <beep/socket.h>
#include <beep/skbuff.h>
#include <beep/kernel.h>
#include <beep/timer.h>
#include <beep/netlink.h>
#include <beep/netdevice.h>
#include <beep/netfilter/x_tables.h>
#include <beep/netfilter_bridge/ebtables.h>
#include <beep/netfilter_bridge/ebt_ulog.h>
#include <net/netfilter/nf_log.h>
#include <net/sock.h>
#include "../br_private.h"

static unsigned int nlbufsiz = NLMSG_GOODSIZE;
module_param(nlbufsiz, uint, 0600);
MODULE_PARM_DESC(nlbufsiz, "netlink buffer size (number of bytes) "
			   "(defaults to 4096)");

static unsigned int flushtimeout = 10;
module_param(flushtimeout, uint, 0600);
MODULE_PARM_DESC(flushtimeout, "buffer flush timeout (hundredths ofa second) "
			       "(defaults to 10)");

typedef struct {
	unsigned int qlen;		/* number of nlmsgs' in the skb */
	struct nlmsghdr *lastnlh;	/* netlink header of last msg in skb */
	struct sk_buff *skb;		/* the pre-allocated skb */
	struct timer_list timer;	/* the timer function */
	spinlock_t lock;		/* the per-queue lock */
} ebt_ulog_buff_t;

static ebt_ulog_buff_t ulog_buffers[EBT_ULOG_MAXNLGROUPS];
static struct sock *ebtulognl;

/* send one ulog_buff_t to userspace */
static void ulog_send(unsigned int nlgroup)
{
	ebt_ulog_buff_t *ub = &ulog_buffers[nlgroup];

	if (timer_pending(&ub->timer))
		del_timer(&ub->timer);

	if (!ub->skb)
		return;

	/* last nlmsg needs NLMSG_DONE */
	if (ub->qlen > 1)
		ub->lastnlh->nlmsg_type = NLMSG_DONE;

	NETLINK_CB(ub->skb).dst_group = nlgroup + 1;
	netlink_broadcast(ebtulognl, ub->skb, 0, nlgroup + 1, GFP_ATOMIC);

	ub->qlen = 0;
	ub->skb = NULL;
}

/* timer function to flush queue in flushtimeout time */
static void ulog_timer(unsigned long data)
{
	spin_lock_bh(&ulog_buffers[data].lock);
	if (ulog_buffers[data].skb)
		ulog_send(data);
	spin_unlock_bh(&ulog_buffers[data].lock);
}

static struct sk_buff *ulog_alloc_skb(unsigned int size)
{
	struct sk_buff *skb;
	unsigned int n;

	n = max(size, nlbufsiz);
	skb = alloc_skb(n, GFP_ATOMIC | __GFP_NOWARN);
	if (!skb) {
		if (n > size) {
			/* try to allocate only as much as we need for
			 * current packet */
			skb = alloc_skb(size, GFP_ATOMIC);
			if (!skb)
				pr_debug("cannot even allocate buffer of size %ub\n",
					 size);
		}
	}

	return skb;
}

static void ebt_ulog_packet(unsigned int hooknr, const struct sk_buff *skb,
   const struct net_device *in, const struct net_device *out,
   const struct ebt_ulog_info *uloginfo, const char *prefix)
{
	ebt_ulog_packet_msg_t *pm;
	size_t size, copy_len;
	struct nlmsghdr *nlh;
	unsigned int group = uloginfo->nlgroup;
	ebt_ulog_buff_t *ub = &ulog_buffers[group];
	spinlock_t *lock = &ub->lock;
	ktime_t kt;

	if ((uloginfo->cprange == 0) ||
	    (uloginfo->cprange > skb->len + ETH_HLEN))
		copy_len = skb->len + ETH_HLEN;
	else
		copy_len = uloginfo->cprange;

	size = NLMSG_SPACE(sizeof(*pm) + copy_len);
	if (size > nlbufsiz) {
		pr_debug("Size %Zd needed, but nlbufsiz=%d\n", size, nlbufsiz);
		return;
	}

	spin_lock_bh(lock);

	if (!ub->skb) {
		if (!(ub->skb = ulog_alloc_skb(size)))
			goto unlock;
	} else if (size > skb_tailroom(ub->skb)) {
		ulog_send(group);

		if (!(ub->skb = ulog_alloc_skb(size)))
			goto unlock;
	}

	nlh = nlmsg_put(ub->skb, 0, ub->qlen, 0,
			size - NLMSG_ALIGN(sizeof(*nlh)), 0);
	if (!nlh) {
		kfree_skb(ub->skb);
		ub->skb = NULL;
		goto unlock;
	}
	ub->qlen++;

	pm = nlmsg_data(nlh);

	/* Fill in the ulog data */
	pm->version = EBT_ULOG_VERSION;
	kt = ktime_get_real();
	pm->stamp = ktime_to_timeval(kt);
	if (ub->qlen == 1)
		ub->skb->tstamp = kt;
	pm->data_len = copy_len;
	pm->mark = skb->mark;
	pm->hook = hooknr;
	if (uloginfo->prefix != NULL)
		strcpy(pm->prefix, uloginfo->prefix);
	else
		*(pm->prefix) = '\0';

	if (in) {
		strcpy(pm->physindev, in->name);
		/* If in isn't a bridge, then physindev==indev */
		if (br_port_exists(in))
			/* rcu_read_lock()ed by nf_hook_slow */
			strcpy(pm->indev, br_port_get_rcu(in)->br->dev->name);
		else
			strcpy(pm->indev, in->name);
	} else
		pm->indev[0] = pm->physindev[0] = '\0';

	if (out) {
		/* If out exists, then out is a bridge port */
		strcpy(pm->physoutdev, out->name);
		/* rcu_read_lock()ed by nf_hook_slow */
		strcpy(pm->outdev, br_port_get_rcu(out)->br->dev->name);
	} else
		pm->outdev[0] = pm->physoutdev[0] = '\0';

	if (skb_copy_bits(skb, -ETH_HLEN, pm->data, copy_len) < 0)
		BUG();

	if (ub->qlen > 1)
		ub->lastnlh->nlmsg_flags |= NLM_F_MULTI;

	ub->lastnlh = nlh;

	if (ub->qlen >= uloginfo->qthreshold)
		ulog_send(group);
	else if (!timer_pending(&ub->timer)) {
		ub->timer.expires = jiffies + flushtimeout * HZ / 100;
		add_timer(&ub->timer);
	}

unlock:
	spin_unlock_bh(lock);
}

/* this function is registered with the netfilter core */
static void ebt_log_packet(u_int8_t pf, unsigned int hooknum,
   const struct sk_buff *skb, const struct net_device *in,
   const struct net_device *out, const struct nf_loginfo *li,
   const char *prefix)
{
	struct ebt_ulog_info loginfo;

	if (!li || li->type != NF_LOG_TYPE_ULOG) {
		loginfo.nlgroup = EBT_ULOG_DEFAULT_NLGROUP;
		loginfo.cprange = 0;
		loginfo.qthreshold = EBT_ULOG_DEFAULT_QTHRESHOLD;
		loginfo.prefix[0] = '\0';
	} else {
		loginfo.nlgroup = li->u.ulog.group;
		loginfo.cprange = li->u.ulog.copy_len;
		loginfo.qthreshold = li->u.ulog.qthreshold;
		strlcpy(loginfo.prefix, prefix, sizeof(loginfo.prefix));
	}

	ebt_ulog_packet(hooknum, skb, in, out, &loginfo, prefix);
}

static unsigned int
ebt_ulog_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	ebt_ulog_packet(par->hooknum, skb, par->in, par->out,
	                par->targinfo, NULL);
	return EBT_CONTINUE;
}

static int ebt_ulog_tg_check(const struct xt_tgchk_param *par)
{
	struct ebt_ulog_info *uloginfo = par->targinfo;

	if (uloginfo->nlgroup > 31)
		return -EINVAL;

	uloginfo->prefix[EBT_ULOG_PREFIX_LEN - 1] = '\0';

	if (uloginfo->qthreshold > EBT_ULOG_MAX_QLEN)
		uloginfo->qthreshold = EBT_ULOG_MAX_QLEN;

	return 0;
}

static struct xt_target ebt_ulog_tg_reg __read_mostly = {
	.name		= "ulog",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.target		= ebt_ulog_tg,
	.checkentry	= ebt_ulog_tg_check,
	.targetsize	= sizeof(struct ebt_ulog_info),
	.me		= THIS_MODULE,
};

static struct nf_logger ebt_ulog_logger __read_mostly = {
	.name		= "ebt_ulog",
	.logfn		= &ebt_log_packet,
	.me		= THIS_MODULE,
};

static int __init ebt_ulog_init(void)
{
	int ret;
	int i;
	struct netlink_kernel_cfg cfg = {
		.groups	= EBT_ULOG_MAXNLGROUPS,
	};

	if (nlbufsiz >= 128*1024) {
		pr_warning("Netlink buffer has to be <= 128kB,"
			   " please try a smaller nlbufsiz parameter.\n");
		return -EINVAL;
	}

	/* initialize ulog_buffers */
	for (i = 0; i < EBT_ULOG_MAXNLGROUPS; i++) {
		setup_timer(&ulog_buffers[i].timer, ulog_timer, i);
		spin_lock_init(&ulog_buffers[i].lock);
	}

	ebtulognl = netlink_kernel_create(&init_net, NETLINK_NFLOG, &cfg);
	if (!ebtulognl)
		ret = -ENOMEM;
	else if ((ret = xt_register_target(&ebt_ulog_tg_reg)) != 0)
		netlink_kernel_release(ebtulognl);

	if (ret == 0)
		nf_log_register(NFPROTO_BRIDGE, &ebt_ulog_logger);

	return ret;
}

static void __exit ebt_ulog_fini(void)
{
	ebt_ulog_buff_t *ub;
	int i;

	nf_log_unregister(&ebt_ulog_logger);
	xt_unregister_target(&ebt_ulog_tg_reg);
	for (i = 0; i < EBT_ULOG_MAXNLGROUPS; i++) {
		ub = &ulog_buffers[i];
		if (timer_pending(&ub->timer))
			del_timer(&ub->timer);
		spin_lock_bh(&ub->lock);
		if (ub->skb) {
			kfree_skb(ub->skb);
			ub->skb = NULL;
		}
		spin_unlock_bh(&ub->lock);
	}
	netlink_kernel_release(ebtulognl);
}

module_init(ebt_ulog_init);
module_exit(ebt_ulog_fini);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bart De Schuymer <bdschuym@pandora.be>");
MODULE_DESCRIPTION("Ebtables: Packet logging to netlink using ULOG");
