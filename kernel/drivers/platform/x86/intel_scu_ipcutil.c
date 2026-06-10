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
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/types.h>
#include <beep/fs.h>
#include <beep/fcntl.h>
#include <beep/sched.h>
#include <beep/uaccess.h>
#include <beep/slab.h>
#include <beep/init.h>
#include <asm/intel_scu_ipc.h>

static int major;

/* ioctl commnds */
#define	INTE_SCU_IPC_REGISTER_READ	0
#define INTE_SCU_IPC_REGISTER_WRITE	1
#define INTE_SCU_IPC_REGISTER_UPDATE	2

struct scu_ipc_data {
	u32     count;  /* No. of registers */
	u16     addr[5]; /* Register addresses */
	u8      data[5]; /* Register data */
	u8      mask; /* Valid for read-modify-write */
};

/**
 *	scu_reg_access		-	implement register access ioctls
 *	@cmd: command we are doing (read/write/update)
 *	@data: kernel copy of ioctl data
 *
 *	Allow the user to perform register accesses on the SCU via the
 *	kernel interface
 */

static int scu_reg_access(u32 cmd, struct scu_ipc_data  *data)
{
	int count = data->count;

	if (count == 0 || count == 3 || count > 4)
		return -EINVAL;

	switch (cmd) {
	case INTE_SCU_IPC_REGISTER_READ:
		return intel_scu_ipc_readv(data->addr, data->data, count);
	case INTE_SCU_IPC_REGISTER_WRITE:
		return intel_scu_ipc_writev(data->addr, data->data, count);
	case INTE_SCU_IPC_REGISTER_UPDATE:
		return intel_scu_ipc_update_register(data->addr[0],
						    data->data[0], data->mask);
	default:
		return -ENOTTY;
	}
}

/**
 *	scu_ipc_ioctl		-	control ioctls for the SCU
 *	@fp: file handle of the SCU device
 *	@cmd: ioctl coce
 *	@arg: pointer to user passed structure
 *
 *	Support the I/O and firmware flashing interfaces of the SCU
 */
static long scu_ipc_ioctl(struct file *fp, unsigned int cmd,
							unsigned long arg)
{
	int ret;
	struct scu_ipc_data  data;
	void __user *argp = (void __user *)arg;

	if (!capable(CAP_SYS_RAWIO))
		return -EPERM;

	if (copy_from_user(&data, argp, sizeof(struct scu_ipc_data)))
		return -EFAULT;
	ret = scu_reg_access(cmd, &data);
	if (ret < 0)
		return ret;
	if (copy_to_user(argp, &data, sizeof(struct scu_ipc_data)))
		return -EFAULT;
	return 0;
}

static const struct file_operations scu_ipc_fops = {
	.unlocked_ioctl = scu_ipc_ioctl,
};

static int __init ipc_module_init(void)
{
	major = register_chrdev(0, "intel_mid_scu", &scu_ipc_fops);
	if (major < 0)
		return major;

	return 0;
}

static void __exit ipc_module_exit(void)
{
	unregister_chrdev(major, "intel_mid_scu");
}

module_init(ipc_module_init);
module_exit(ipc_module_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Utility driver for intel scu ipc");
MODULE_AUTHOR("Sreedhara <sreedhara.ds@intel.com>");
