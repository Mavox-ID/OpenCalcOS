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

#define ts_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))
static int ts_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_LOGIVENDOR)
		return 0;

	switch (usage->hid & HID_USAGE) {
        case 0x046: ts_map_key_clear(KEY_YELLOW);         break;
        case 0x047: ts_map_key_clear(KEY_GREEN);          break;
        case 0x049: ts_map_key_clear(KEY_BLUE);           break;
        case 0x04a: ts_map_key_clear(KEY_RED);		  break;
        case 0x00d: ts_map_key_clear(KEY_HOME);           break;
        case 0x025: ts_map_key_clear(KEY_TV);             break;
        case 0x048: ts_map_key_clear(KEY_VCR);            break;
        case 0x024: ts_map_key_clear(KEY_MENU);           break;
        default:
        return 0;
	}

	return 1;
}

static const struct hid_device_id ts_devices[] = {
	{ HID_USB_DEVICE( USB_VENDOR_ID_LCPOWER, USB_DEVICE_ID_LCPOWER_LC1000) },
	{ }
};
MODULE_DEVICE_TABLE(hid, ts_devices);

static struct hid_driver ts_driver = {
	.name = "LC RC1000MCE",
	.id_table = ts_devices,
	.input_mapping = ts_input_mapping,
};

static int __init ts_init(void)
{
	return hid_register_driver(&ts_driver);
}

static void __exit ts_exit(void)
{
	hid_unregister_driver(&ts_driver);
}

module_init(ts_init);
module_exit(ts_exit);
MODULE_LICENSE("GPL");
