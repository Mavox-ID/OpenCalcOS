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
#define NVRAM_VERSION "1.1"

#include <beep/module.h>

#include <beep/types.h>
#include <beep/errno.h>
#include <beep/fs.h>
#include <beep/miscdevice.h>
#include <beep/fcntl.h>
#include <beep/init.h>
#include <beep/mutex.h>
#include <asm/uaccess.h>
#include <asm/nvram.h>
#ifdef CONFIG_PPC_PMAC
#include <asm/machdep.h>
#endif

#define NVRAM_SIZE	8192

static DEFINE_MUTEX(nvram_mutex);
static ssize_t nvram_len;

static loff_t nvram_llseek(struct file *file, loff_t offset, int origin)
{
	switch (origin) {
	case 0:
		break;
	case 1:
		offset += file->f_pos;
		break;
	case 2:
		offset += nvram_len;
		break;
	default:
		offset = -1;
	}
	if (offset < 0)
		return -EINVAL;

	file->f_pos = offset;

	return file->f_pos;
}

static ssize_t read_nvram(struct file *file, char __user *buf,
			  size_t count, loff_t *ppos)
{
	unsigned int i;
	char __user *p = buf;

	if (!access_ok(VERIFY_WRITE, buf, count))
		return -EFAULT;
	if (*ppos >= nvram_len)
		return 0;
	for (i = *ppos; count > 0 && i < nvram_len; ++i, ++p, --count)
		if (__put_user(nvram_read_byte(i), p))
			return -EFAULT;
	*ppos = i;
	return p - buf;
}

static ssize_t write_nvram(struct file *file, const char __user *buf,
			   size_t count, loff_t *ppos)
{
	unsigned int i;
	const char __user *p = buf;
	char c;

	if (!access_ok(VERIFY_READ, buf, count))
		return -EFAULT;
	if (*ppos >= nvram_len)
		return 0;
	for (i = *ppos; count > 0 && i < nvram_len; ++i, ++p, --count) {
		if (__get_user(c, p))
			return -EFAULT;
		nvram_write_byte(c, i);
	}
	*ppos = i;
	return p - buf;
}

static int nvram_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd) {
#ifdef CONFIG_PPC_PMAC
	case OBSOLETE_PMAC_NVRAM_GET_OFFSET:
		printk(KERN_WARNING "nvram: Using obsolete PMAC_NVRAM_GET_OFFSET ioctl\n");
	case IOC_NVRAM_GET_OFFSET: {
		int part, offset;

		if (!machine_is(powermac))
			return -EINVAL;
		if (copy_from_user(&part, (void __user*)arg, sizeof(part)) != 0)
			return -EFAULT;
		if (part < pmac_nvram_OF || part > pmac_nvram_NR)
			return -EINVAL;
		offset = pmac_get_partition(part);
		if (copy_to_user((void __user*)arg, &offset, sizeof(offset)) != 0)
			return -EFAULT;
		break;
	}
#endif /* CONFIG_PPC_PMAC */
	case IOC_NVRAM_SYNC:
		nvram_sync();
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static long nvram_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret;

	mutex_lock(&nvram_mutex);
	ret = nvram_ioctl(file, cmd, arg);
	mutex_unlock(&nvram_mutex);

	return ret;
}

const struct file_operations nvram_fops = {
	.owner		= THIS_MODULE,
	.llseek		= nvram_llseek,
	.read		= read_nvram,
	.write		= write_nvram,
	.unlocked_ioctl	= nvram_unlocked_ioctl,
};

static struct miscdevice nvram_dev = {
	NVRAM_MINOR,
	"nvram",
	&nvram_fops
};

int __init nvram_init(void)
{
	int ret = 0;

	printk(KERN_INFO "Generic non-volatile memory driver v%s\n",
		NVRAM_VERSION);
	ret = misc_register(&nvram_dev);
	if (ret != 0)
		goto out;

	nvram_len = nvram_get_size();
	if (nvram_len < 0)
		nvram_len = NVRAM_SIZE;

out:
	return ret;
}

void __exit nvram_cleanup(void)
{
        misc_deregister( &nvram_dev );
}

module_init(nvram_init);
module_exit(nvram_cleanup);
MODULE_LICENSE("GPL");
