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
#include <beep/fs.h>
#include <beep/mm.h>
#include <beep/miscdevice.h>
#include <beep/watchdog.h>
#include <beep/reboot.h>
#include <beep/mutex.h>
#include <beep/init.h>
#include <beep/spinlock.h>
#include <asm/uaccess.h>
#include "mconsole.h"

MODULE_LICENSE("GPL");

static DEFINE_MUTEX(harddog_mutex);
static DEFINE_SPINLOCK(lock);
static int timer_alive;
static int harddog_in_fd = -1;
static int harddog_out_fd = -1;

/*
 *	Allow only one person to hold it open
 */

extern int start_watchdog(int *in_fd_ret, int *out_fd_ret, char *sock);

static int harddog_open(struct inode *inode, struct file *file)
{
	int err = -EBUSY;
	char *sock = NULL;

	mutex_lock(&harddog_mutex);
	spin_lock(&lock);
	if(timer_alive)
		goto err;
#ifdef CONFIG_WATCHDOG_NOWAYOUT
	__module_get(THIS_MODULE);
#endif

#ifdef CONFIG_MCONSOLE
	sock = mconsole_notify_socket();
#endif
	err = start_watchdog(&harddog_in_fd, &harddog_out_fd, sock);
	if(err)
		goto err;

	timer_alive = 1;
	spin_unlock(&lock);
	mutex_unlock(&harddog_mutex);
	return nonseekable_open(inode, file);
err:
	spin_unlock(&lock);
	mutex_unlock(&harddog_mutex);
	return err;
}

extern void stop_watchdog(int in_fd, int out_fd);

static int harddog_release(struct inode *inode, struct file *file)
{
	/*
	 *	Shut off the timer.
	 */

	spin_lock(&lock);

	stop_watchdog(harddog_in_fd, harddog_out_fd);
	harddog_in_fd = -1;
	harddog_out_fd = -1;

	timer_alive=0;
	spin_unlock(&lock);

	return 0;
}

extern int ping_watchdog(int fd);

static ssize_t harddog_write(struct file *file, const char __user *data, size_t len,
			     loff_t *ppos)
{
	/*
	 *	Refresh the timer.
	 */
	if(len)
		return ping_watchdog(harddog_out_fd);
	return 0;
}

static int harddog_ioctl_unlocked(struct file *file,
				  unsigned int cmd, unsigned long arg)
{
	void __user *argp= (void __user *)arg;
	static struct watchdog_info ident = {
		WDIOC_SETTIMEOUT,
		0,
		"UML Hardware Watchdog"
	};
	switch (cmd) {
		default:
			return -ENOTTY;
		case WDIOC_GETSUPPORT:
			if(copy_to_user(argp, &ident, sizeof(ident)))
				return -EFAULT;
			return 0;
		case WDIOC_GETSTATUS:
		case WDIOC_GETBOOTSTATUS:
			return put_user(0,(int __user *)argp);
		case WDIOC_KEEPALIVE:
			return ping_watchdog(harddog_out_fd);
	}
}

static long harddog_ioctl(struct file *file,
			  unsigned int cmd, unsigned long arg)
{
	long ret;

	mutex_lock(&harddog_mutex);
	ret = harddog_ioctl_unlocked(file, cmd, arg);
	mutex_unlock(&harddog_mutex);

	return ret;
}

static const struct file_operations harddog_fops = {
	.owner		= THIS_MODULE,
	.write		= harddog_write,
	.unlocked_ioctl	= harddog_ioctl,
	.open		= harddog_open,
	.release	= harddog_release,
	.llseek		= no_llseek,
};

static struct miscdevice harddog_miscdev = {
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &harddog_fops,
};

static char banner[] __initdata = KERN_INFO "UML Watchdog Timer\n";

static int __init harddog_init(void)
{
	int ret;

	ret = misc_register(&harddog_miscdev);

	if (ret)
		return ret;

	printk(banner);

	return 0;
}

static void __exit harddog_exit(void)
{
	misc_deregister(&harddog_miscdev);
}

module_init(harddog_init);
module_exit(harddog_exit);
