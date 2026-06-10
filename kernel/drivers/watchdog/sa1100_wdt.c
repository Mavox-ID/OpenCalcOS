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
#include <beep/moduleparam.h>
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/fs.h>
#include <beep/miscdevice.h>
#include <beep/watchdog.h>
#include <beep/init.h>
#include <beep/io.h>
#include <beep/bitops.h>
#include <beep/uaccess.h>
#include <beep/timex.h>

#ifdef CONFIG_ARCH_PXA
#include <mach/regs-ost.h>
#endif

#include <mach/reset.h>
#include <mach/hardware.h>

static unsigned long oscr_freq;
static unsigned long sa1100wdt_users;
static unsigned int pre_margin;
static int boot_status;

/*
 *	Allow only one person to hold it open
 */
static int sa1100dog_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(1, &sa1100wdt_users))
		return -EBUSY;

	/* Activate SA1100 Watchdog timer */
	writel_relaxed(readl_relaxed(OSCR) + pre_margin, OSMR3);
	writel_relaxed(OSSR_M3, OSSR);
	writel_relaxed(OWER_WME, OWER);
	writel_relaxed(readl_relaxed(OIER) | OIER_E3, OIER);
	return nonseekable_open(inode, file);
}

/*
 * The watchdog cannot be disabled.
 *
 * Previous comments suggested that turning off the interrupt by
 * clearing OIER[E3] would prevent the watchdog timing out but this
 * does not appear to be true (at least on the PXA255).
 */
static int sa1100dog_release(struct inode *inode, struct file *file)
{
	pr_crit("Device closed - timer will not stop\n");
	clear_bit(1, &sa1100wdt_users);
	return 0;
}

static ssize_t sa1100dog_write(struct file *file, const char __user *data,
						size_t len, loff_t *ppos)
{
	if (len)
		/* Refresh OSMR3 timer. */
		writel_relaxed(readl_relaxed(OSCR) + pre_margin, OSMR3);
	return len;
}

static const struct watchdog_info ident = {
	.options	= WDIOF_CARDRESET | WDIOF_SETTIMEOUT
				| WDIOF_KEEPALIVEPING,
	.identity	= "SA1100/PXA255 Watchdog",
	.firmware_version	= 1,
};

static long sa1100dog_ioctl(struct file *file, unsigned int cmd,
							unsigned long arg)
{
	int ret = -ENOTTY;
	int time;
	void __user *argp = (void __user *)arg;
	int __user *p = argp;

	switch (cmd) {
	case WDIOC_GETSUPPORT:
		ret = copy_to_user(argp, &ident,
				   sizeof(ident)) ? -EFAULT : 0;
		break;

	case WDIOC_GETSTATUS:
		ret = put_user(0, p);
		break;

	case WDIOC_GETBOOTSTATUS:
		ret = put_user(boot_status, p);
		break;

	case WDIOC_KEEPALIVE:
		writel_relaxed(readl_relaxed(OSCR) + pre_margin, OSMR3);
		ret = 0;
		break;

	case WDIOC_SETTIMEOUT:
		ret = get_user(time, p);
		if (ret)
			break;

		if (time <= 0 || (oscr_freq * (long long)time >= 0xffffffff)) {
			ret = -EINVAL;
			break;
		}

		pre_margin = oscr_freq * time;
		writel_relaxed(readl_relaxed(OSCR) + pre_margin, OSMR3);
		/*fall through*/

	case WDIOC_GETTIMEOUT:
		ret = put_user(pre_margin / oscr_freq, p);
		break;
	}
	return ret;
}

static const struct file_operations sa1100dog_fops = {
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.write		= sa1100dog_write,
	.unlocked_ioctl	= sa1100dog_ioctl,
	.open		= sa1100dog_open,
	.release	= sa1100dog_release,
};

static struct miscdevice sa1100dog_miscdev = {
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &sa1100dog_fops,
};

static int margin __initdata = 60;		/* (secs) Default is 1 minute */

static int __init sa1100dog_init(void)
{
	int ret;

	oscr_freq = get_clock_tick_rate();

	/*
	 * Read the reset status, and save it for later.  If
	 * we suspend, RCSR will be cleared, and the watchdog
	 * reset reason will be lost.
	 */
	boot_status = (reset_status & RESET_STATUS_WATCHDOG) ?
				WDIOF_CARDRESET : 0;
	pre_margin = oscr_freq * margin;

	ret = misc_register(&sa1100dog_miscdev);
	if (ret == 0)
		pr_info("SA1100/PXA2xx Watchdog Timer: timer margin %d sec\n",
			margin);
	return ret;
}

static void __exit sa1100dog_exit(void)
{
	misc_deregister(&sa1100dog_miscdev);
}

module_init(sa1100dog_init);
module_exit(sa1100dog_exit);

MODULE_AUTHOR("Oleg Drokin <green@crimea.edu>");
MODULE_DESCRIPTION("SA1100/PXA2xx Watchdog");

module_param(margin, int, 0);
MODULE_PARM_DESC(margin, "Watchdog margin in seconds (default 60s)");

MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(WATCHDOG_MINOR);
