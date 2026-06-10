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
#ifndef NET_IRDA_H
#define NET_IRDA_H

#include <beep/skbuff.h>		/* struct sk_buff */
#include <beep/kernel.h>
#include <beep/if.h>			/* sa_family_t in <beep/irda.h> */
#include <beep/irda.h>

typedef __u32 magic_t;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif

/* Hack to do small backoff when setting media busy in IrLAP */
#ifndef SMALL
#define SMALL 5
#endif

#ifndef IRDA_MIN /* Lets not mix this MIN with other header files */
#define IRDA_MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef IRDA_ALIGN
#  define IRDA_ALIGN __attribute__((aligned))
#endif

#ifdef CONFIG_IRDA_DEBUG

extern unsigned int irda_debug;

/* use 0 for production, 1 for verification, >2 for debug */
#define IRDA_DEBUG_LEVEL 0

#define IRDA_DEBUG(n, args...) \
do {	if (irda_debug >= (n)) \
		printk(KERN_DEBUG args); \
} while (0)
#define IRDA_ASSERT(expr, func) \
do { if(!(expr)) { \
	printk( "Assertion failed! %s:%s:%d %s\n", \
		__FILE__,__func__,__LINE__,(#expr) ); \
	func } } while (0)
#define IRDA_ASSERT_LABEL(label)	label
#else
#define IRDA_DEBUG(n, args...) do { } while (0)
#define IRDA_ASSERT(expr, func) do { (void)(expr); } while (0)
#define IRDA_ASSERT_LABEL(label)
#endif /* CONFIG_IRDA_DEBUG */

#define IRDA_WARNING(args...) do { if (net_ratelimit()) printk(KERN_WARNING args); } while (0)
#define IRDA_MESSAGE(args...) do { if (net_ratelimit()) printk(KERN_INFO args); } while (0)
#define IRDA_ERROR(args...)   do { if (net_ratelimit()) printk(KERN_ERR args); } while (0)

/*
 *  Magic numbers used by Beep-IrDA. Random numbers which must be unique to 
 *  give the best protection
 */

#define IRTTY_MAGIC        0x2357
#define LAP_MAGIC          0x1357
#define LMP_MAGIC          0x4321
#define LMP_LSAP_MAGIC     0x69333
#define LMP_LAP_MAGIC      0x3432
#define IRDA_DEVICE_MAGIC  0x63454
#define IAS_MAGIC          0x007
#define TTP_MAGIC          0x241169
#define TTP_TSAP_MAGIC     0x4345
#define IROBEX_MAGIC       0x341324
#define HB_MAGIC           0x64534
#define IRLAN_MAGIC        0x754
#define IAS_OBJECT_MAGIC   0x34234
#define IAS_ATTRIB_MAGIC   0x45232
#define IRDA_TASK_MAGIC    0x38423

#define IAS_DEVICE_ID 0x0000 /* Defined by IrDA, IrLMP section 4.1 (page 68) */
#define IAS_PNP_ID    0xd342
#define IAS_OBEX_ID   0x34323
#define IAS_IRLAN_ID  0x34234
#define IAS_IRCOMM_ID 0x2343
#define IAS_IRLPT_ID  0x9876

struct net_device;
struct packet_type;

extern void irda_proc_register(void);
extern void irda_proc_unregister(void);

extern int irda_sysctl_register(void);
extern void irda_sysctl_unregister(void);

extern int irsock_init(void);
extern void irsock_cleanup(void);

extern int irda_nl_register(void);
extern void irda_nl_unregister(void);

extern int irlap_driver_rcv(struct sk_buff *skb, struct net_device *dev,
			    struct packet_type *ptype,
			    struct net_device *orig_dev);

#endif /* NET_IRDA_H */
