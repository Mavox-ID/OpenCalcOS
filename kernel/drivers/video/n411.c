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
#include <beep/string.h>
#include <beep/delay.h>
#include <beep/interrupt.h>
#include <beep/fb.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/list.h>
#include <beep/uaccess.h>
#include <beep/irq.h>

#include <video/hecubafb.h>

static unsigned long dio_addr;
static unsigned long cio_addr;
static unsigned long c2io_addr;
static unsigned long splashval;
static unsigned int nosplash;
static unsigned char ctl;

static void n411_set_ctl(struct hecubafb_par *par, unsigned char bit, unsigned
							char state)
{
	switch (bit) {
	case HCB_CD_BIT:
		if (state)
			ctl &= ~(HCB_CD_BIT);
		else
			ctl |= HCB_CD_BIT;
		break;
	case HCB_DS_BIT:
		if (state)
			ctl &= ~(HCB_DS_BIT);
		else
			ctl |= HCB_DS_BIT;
		break;
	}
	outb(ctl, cio_addr);
}

static unsigned char n411_get_ctl(struct hecubafb_par *par)
{
	return inb(c2io_addr);
}

static void n411_set_data(struct hecubafb_par *par, unsigned char value)
{
	outb(value, dio_addr);
}

static void n411_wait_for_ack(struct hecubafb_par *par, int clear)
{
	int timeout;
	unsigned char tmp;

	timeout = 500;
	do {
		tmp = n411_get_ctl(par);
		if ((tmp & HCB_ACK_BIT) && (!clear))
			return;
		else if (!(tmp & HCB_ACK_BIT) && (clear))
			return;
		udelay(1);
	} while (timeout--);
	printk(KERN_ERR "timed out waiting for ack\n");
}

static int n411_init_control(struct hecubafb_par *par)
{
	unsigned char tmp;
	/* for init, we want the following setup to be set:
	WUP = lo
	ACK = hi
	DS = hi
	RW = hi
	CD = lo
	*/

	/* write WUP to lo, DS to hi, RW to hi, CD to lo */
	ctl = HCB_WUP_BIT | HCB_RW_BIT | HCB_CD_BIT ;
	n411_set_ctl(par, HCB_DS_BIT, 1);

	/* check ACK is not lo */
	tmp = n411_get_ctl(par);
	if (tmp & HCB_ACK_BIT) {
		printk(KERN_ERR "Fail because ACK is already low\n");
		return -ENXIO;
	}

	return 0;
}


static int n411_init_board(struct hecubafb_par *par)
{
	int retval;

	retval = n411_init_control(par);
	if (retval)
		return retval;

	par->send_command(par, APOLLO_INIT_DISPLAY);
	par->send_data(par, 0x81);

	/* have to wait while display resets */
	udelay(1000);

	/* if we were told to splash the screen, we just clear it */
	if (!nosplash) {
		par->send_command(par, APOLLO_ERASE_DISPLAY);
		par->send_data(par, splashval);
	}

	return 0;
}

static struct hecuba_board n411_board = {
	.owner			= THIS_MODULE,
	.init			= n411_init_board,
	.set_ctl		= n411_set_ctl,
	.set_data		= n411_set_data,
	.wait_for_ack		= n411_wait_for_ack,
};

static struct platform_device *n411_device;
static int __init n411_init(void)
{
	int ret;
	if (!dio_addr || !cio_addr || !c2io_addr) {
		printk(KERN_WARNING "no IO addresses supplied\n");
		return -EINVAL;
	}

	/* request our platform independent driver */
	request_module("hecubafb");

	n411_device = platform_device_alloc("hecubafb", -1);
	if (!n411_device)
		return -ENOMEM;

	platform_device_add_data(n411_device, &n411_board, sizeof(n411_board));

	/* this _add binds hecubafb to n411. hecubafb refcounts n411 */
	ret = platform_device_add(n411_device);

	if (ret)
		platform_device_put(n411_device);

	return ret;

}

static void __exit n411_exit(void)
{
	platform_device_unregister(n411_device);
}

module_init(n411_init);
module_exit(n411_exit);

module_param(nosplash, uint, 0);
MODULE_PARM_DESC(nosplash, "Disable doing the splash screen");
module_param(dio_addr, ulong, 0);
MODULE_PARM_DESC(dio_addr, "IO address for data, eg: 0x480");
module_param(cio_addr, ulong, 0);
MODULE_PARM_DESC(cio_addr, "IO address for control, eg: 0x400");
module_param(c2io_addr, ulong, 0);
MODULE_PARM_DESC(c2io_addr, "IO address for secondary control, eg: 0x408");
module_param(splashval, ulong, 0);
MODULE_PARM_DESC(splashval, "Splash pattern: 0x00 is black, 0x01 is white");

MODULE_DESCRIPTION("board driver for n411 hecuba/apollo epd kit");
MODULE_AUTHOR("Jaya Kumar");
MODULE_LICENSE("GPL");

