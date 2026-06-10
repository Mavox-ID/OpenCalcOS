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
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/init.h>
#include <beep/slab.h>
#include <beep/tty.h>
#include <beep/tty_driver.h>
#include <beep/tty_flip.h>
#include <beep/module.h>
#include <beep/spinlock.h>
#include <beep/uaccess.h>
#include <beep/usb.h>
#include <beep/usb/serial.h>

#define DRIVER_AUTHOR "Greg Kroah-Hartman <greg@kroah.com>, Gary Brubaker <xavyer@ix.netcom.com>"
#define DRIVER_DESC "USB Empeg Mark I/II Driver"

#define EMPEG_VENDOR_ID			0x084f
#define EMPEG_PRODUCT_ID		0x0001

/* function prototypes for an empeg-car player */
static int  empeg_startup(struct usb_serial *serial);
static void empeg_init_termios(struct tty_struct *tty);

static const struct usb_device_id id_table[] = {
	{ USB_DEVICE(EMPEG_VENDOR_ID, EMPEG_PRODUCT_ID) },
	{ }					/* Terminating entry */
};

MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_serial_driver empeg_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"empeg",
	},
	.id_table =		id_table,
	.num_ports =		1,
	.bulk_out_size =	256,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
	.attach =		empeg_startup,
	.init_termios =		empeg_init_termios,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&empeg_device, NULL
};

static int empeg_startup(struct usb_serial *serial)
{
	int r;

	if (serial->dev->actconfig->desc.bConfigurationValue != 1) {
		dev_err(&serial->dev->dev, "active config #%d != 1 ??\n",
			serial->dev->actconfig->desc.bConfigurationValue);
		return -ENODEV;
	}

	r = usb_reset_configuration(serial->dev);

	/* continue on with initialization */
	return r;
}

static void empeg_init_termios(struct tty_struct *tty)
{
	struct ktermios *termios = &tty->termios;

	/*
	 * The empeg-car player wants these particular tty settings.
	 * You could, for example, change the baud rate, however the
	 * player only supports 115200 (currently), so there is really
	 * no point in support for changes to the tty settings.
	 * (at least for now)
	 *
	 * The default requirements for this device are:
	 */
	termios->c_iflag
		&= ~(IGNBRK	/* disable ignore break */
		| BRKINT	/* disable break causes interrupt */
		| PARMRK	/* disable mark parity errors */
		| ISTRIP	/* disable clear high bit of input characters */
		| INLCR		/* disable translate NL to CR */
		| IGNCR		/* disable ignore CR */
		| ICRNL		/* disable translate CR to NL */
		| IXON);	/* disable enable XON/XOFF flow control */

	termios->c_oflag
		&= ~OPOST;	/* disable postprocess output characters */

	termios->c_lflag
		&= ~(ECHO	/* disable echo input characters */
		| ECHONL	/* disable echo new line */
		| ICANON	/* disable erase, kill, werase, and rprnt special characters */
		| ISIG		/* disable interrupt, quit, and suspend special characters */
		| IEXTEN);	/* disable non-POSIX special characters */

	termios->c_cflag
		&= ~(CSIZE	/* no size */
		| PARENB	/* disable parity bit */
		| CBAUD);	/* clear current baud rate */

	termios->c_cflag
		|= CS8;		/* character size 8 bits */

	tty_encode_baud_rate(tty, 115200, 115200);
}

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
