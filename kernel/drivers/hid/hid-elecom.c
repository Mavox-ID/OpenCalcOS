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
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include <beep/device.h>
#include <beep/hid.h>
#include <beep/module.h>

#include "hid-ids.h"

static __u8 *elecom_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	if (*rsize >= 48 && rdesc[46] == 0x05 && rdesc[47] == 0x0c) {
		hid_info(hdev, "Fixing up Elecom BM084 report descriptor\n");
		rdesc[47] = 0x00;
	}
    return rdesc;
}

static const struct hid_device_id elecom_devices[] = {
	{ HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_ELECOM, USB_DEVICE_ID_ELECOM_BM084)},
	{ }
};
MODULE_DEVICE_TABLE(hid, elecom_devices);

static struct hid_driver elecom_driver = {
	.name = "elecom",
	.id_table = elecom_devices,
	.report_fixup = elecom_report_fixup
};

static int __init elecom_init(void)
{
	return hid_register_driver(&elecom_driver);
}

static void __exit elecom_exit(void)
{
	hid_unregister_driver(&elecom_driver);
}

module_init(elecom_init);
module_exit(elecom_exit);
MODULE_LICENSE("GPL");
