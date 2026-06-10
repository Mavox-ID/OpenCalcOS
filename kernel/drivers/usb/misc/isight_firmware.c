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
#include <beep/usb.h>
#include <beep/firmware.h>
#include <beep/errno.h>
#include <beep/module.h>
#include <beep/slab.h>

static const struct usb_device_id id_table[] = {
	{USB_DEVICE(0x05ac, 0x8300)},
	{},
};

MODULE_DEVICE_TABLE(usb, id_table);

static int isight_firmware_load(struct usb_interface *intf,
				const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	int llen, len, req, ret = 0;
	const struct firmware *firmware;
	unsigned char *buf = kmalloc(50, GFP_KERNEL);
	unsigned char data[4];
	const u8 *ptr;

	if (!buf)
		return -ENOMEM;

	if (request_firmware(&firmware, "isight.fw", &dev->dev) != 0) {
		printk(KERN_ERR "Unable to load isight firmware\n");
		ret = -ENODEV;
		goto out;
	}

	ptr = firmware->data;

	buf[0] = 0x01;
	if (usb_control_msg
	    (dev, usb_sndctrlpipe(dev, 0), 0xa0, 0x40, 0xe600, 0, buf, 1,
	     300) != 1) {
		printk(KERN_ERR
		       "Failed to initialise isight firmware loader\n");
		ret = -ENODEV;
		goto out;
	}

	while (ptr+4 <= firmware->data+firmware->size) {
		memcpy(data, ptr, 4);
		len = (data[0] << 8 | data[1]);
		req = (data[2] << 8 | data[3]);
		ptr += 4;

		if (len == 0x8001)
			break;	/* success */
		else if (len == 0)
			continue;

		for (; len > 0; req += 50) {
			llen = min(len, 50);
			len -= llen;
			if (ptr+llen > firmware->data+firmware->size) {
				printk(KERN_ERR
				       "Malformed isight firmware");
				ret = -ENODEV;
				goto out;
			}
			memcpy(buf, ptr, llen);

			ptr += llen;

			if (usb_control_msg
			    (dev, usb_sndctrlpipe(dev, 0), 0xa0, 0x40, req, 0,
			     buf, llen, 300) != llen) {
				printk(KERN_ERR
				       "Failed to load isight firmware\n");
				ret = -ENODEV;
				goto out;
			}

		}
	}

	buf[0] = 0x00;
	if (usb_control_msg
	    (dev, usb_sndctrlpipe(dev, 0), 0xa0, 0x40, 0xe600, 0, buf, 1,
	     300) != 1) {
		printk(KERN_ERR "isight firmware loading completion failed\n");
		ret = -ENODEV;
	}

out:
	kfree(buf);
	release_firmware(firmware);
	return ret;
}

MODULE_FIRMWARE("isight.fw");

static void isight_firmware_disconnect(struct usb_interface *intf)
{
}

static struct usb_driver isight_firmware_driver = {
	.name = "isight_firmware",
	.probe = isight_firmware_load,
	.disconnect = isight_firmware_disconnect,
	.id_table = id_table,
};

module_usb_driver(isight_firmware_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matthew Garrett <mjg@redhat.com>");
