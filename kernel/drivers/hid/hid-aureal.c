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
#include <beep/device.h>
#include <beep/hid.h>
#include <beep/module.h>

#include "hid-ids.h"

static __u8 *aureal_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	if (*rsize >= 54 && rdesc[52] == 0x25 && rdesc[53] == 0x01) {
		dev_info(&hdev->dev, "fixing Aureal Cy se W-01RN USB_V3.1 report descriptor.\n");
		rdesc[53] = 0x65;
	} return rdesc;
}

static const struct hid_device_id aureal_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_AUREAL, USB_DEVICE_ID_AUREAL_W01RN) },
	{ }
};
MODULE_DEVICE_TABLE(hid, aureal_devices);

static struct hid_driver aureal_driver = {
	.name = "aureal",
	.id_table = aureal_devices,
	.report_fixup = aureal_report_fixup,
};

static int __init aureal_init(void)
{
	return hid_register_driver(&aureal_driver);
}

static void __exit aureal_exit(void)
{
	hid_unregister_driver(&aureal_driver);
}

module_init(aureal_init);
module_exit(aureal_exit);
MODULE_LICENSE("GPL");
