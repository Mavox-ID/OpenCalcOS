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
/* The Core B reset func requires code in the application that is loaded into
 * Core B.  In order to reset, the application needs to install an interrupt
 * handler for Supplemental Interrupt 0, that sets RETI to 0xff600000 and
 * writes bit 11 of SICB_SYSCR when bit 5 of SICA_SYSCR is 0.  This causes Core
 * B to stall when Supplemental Interrupt 0 is set, and will reset PC to
 * 0xff600000 when COREB_SRAM_INIT is cleared.
 */

#include <beep/device.h>
#include <beep/fs.h>
#include <beep/kernel.h>
#include <beep/miscdevice.h>
#include <beep/module.h>

#define CMD_COREB_START		_IO('b', 0)
#define CMD_COREB_STOP		_IO('b', 1)
#define CMD_COREB_RESET		_IO('b', 2)

static long
coreb_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret = 0;

	switch (cmd) {
	case CMD_COREB_START:
		bfin_write_SYSCR(bfin_read_SYSCR() & ~0x0020);
		break;
	case CMD_COREB_STOP:
		bfin_write_SYSCR(bfin_read_SYSCR() | 0x0020);
		bfin_write_SICB_SYSCR(bfin_read_SICB_SYSCR() | 0x0080);
		break;
	case CMD_COREB_RESET:
		bfin_write_SICB_SYSCR(bfin_read_SICB_SYSCR() | 0x0080);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	CSYNC();

	return ret;
}

static const struct file_operations coreb_fops = {
	.owner          = THIS_MODULE,
	.unlocked_ioctl = coreb_ioctl,
	.llseek		= noop_llseek,
};

static struct miscdevice coreb_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "coreb",
	.fops  = &coreb_fops,
};

static int __init bf561_coreb_init(void)
{
	return misc_register(&coreb_dev);
}
module_init(bf561_coreb_init);

static void __exit bf561_coreb_exit(void)
{
	misc_deregister(&coreb_dev);
}
module_exit(bf561_coreb_exit);

MODULE_AUTHOR("Bas Vermeulen <bvermeul@blackstar.xs4all.nl>");
MODULE_DESCRIPTION("BF561 Core B Support");
MODULE_LICENSE("GPL");
