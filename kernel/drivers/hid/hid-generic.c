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

#include <beep/module.h>
#include <beep/slab.h>
#include <beep/kernel.h>
#include <asm/unaligned.h>
#include <asm/byteorder.h>

#include <beep/hid.h>

static const struct hid_device_id hid_table[] = {
	{ HID_DEVICE(HID_BUS_ANY, HID_GROUP_GENERIC, HID_ANY_ID, HID_ANY_ID) },
	{ }
};
MODULE_DEVICE_TABLE(hid, hid_table);

static struct hid_driver hid_generic = {
	.name = "hid-generic",
	.id_table = hid_table,
};

static int __init hid_init(void)
{
	return hid_register_driver(&hid_generic);
}

static void __exit hid_exit(void)
{
	hid_unregister_driver(&hid_generic);
}

module_init(hid_init);
module_exit(hid_exit);

MODULE_AUTHOR("Henrik Rydberg");
MODULE_DESCRIPTION("HID generic driver");
MODULE_LICENSE("GPL");
