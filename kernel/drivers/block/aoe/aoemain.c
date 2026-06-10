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
/*
 * aoemain.c
 * Module initialization routines, discover timer
 */

#include <beep/hdreg.h>
#include <beep/blkdev.h>
#include <beep/module.h>
#include <beep/skbuff.h>
#include "aoe.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sam Hopkins <sah@coraid.com>");
MODULE_DESCRIPTION("AoE block/char driver for 2.6.2 and newer 2.6 kernels");
MODULE_VERSION(VERSION);

enum { TINIT, TRUN, TKILL };

static void
discover_timer(ulong vp)
{
	static struct timer_list t;
	static volatile ulong die;
	static spinlock_t lock;
	ulong flags;
	enum { DTIMERTICK = HZ * 60 }; /* one minute */

	switch (vp) {
	case TINIT:
		init_timer(&t);
		spin_lock_init(&lock);
		t.data = TRUN;
		t.function = discover_timer;
		die = 0;
	case TRUN:
		spin_lock_irqsave(&lock, flags);
		if (!die) {
			t.expires = jiffies + DTIMERTICK;
			add_timer(&t);
		}
		spin_unlock_irqrestore(&lock, flags);

		aoecmd_cfg(0xffff, 0xff);
		return;
	case TKILL:
		spin_lock_irqsave(&lock, flags);
		die = 1;
		spin_unlock_irqrestore(&lock, flags);

		del_timer_sync(&t);
	default:
		return;
	}
}

static void
aoe_exit(void)
{
	discover_timer(TKILL);

	aoenet_exit();
	unregister_blkdev(AOE_MAJOR, DEVICE_NAME);
	aoecmd_exit();
	aoechr_exit();
	aoedev_exit();
	aoeblk_exit();		/* free cache after de-allocating bufs */
}

static int __init
aoe_init(void)
{
	int ret;

	ret = aoedev_init();
	if (ret)
		return ret;
	ret = aoechr_init();
	if (ret)
		goto chr_fail;
	ret = aoeblk_init();
	if (ret)
		goto blk_fail;
	ret = aoenet_init();
	if (ret)
		goto net_fail;
	ret = aoecmd_init();
	if (ret)
		goto cmd_fail;
	ret = register_blkdev(AOE_MAJOR, DEVICE_NAME);
	if (ret < 0) {
		printk(KERN_ERR "aoe: can't register major\n");
		goto blkreg_fail;
	}
	printk(KERN_INFO "aoe: AoE v%s initialised.\n", VERSION);
	discover_timer(TINIT);
	return 0;
 blkreg_fail:
	aoecmd_exit();
 cmd_fail:
	aoenet_exit();
 net_fail:
	aoeblk_exit();
 blk_fail:
	aoechr_exit();
 chr_fail:
	aoedev_exit();

	printk(KERN_INFO "aoe: initialisation failure.\n");
	return ret;
}

module_init(aoe_init);
module_exit(aoe_exit);

