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
#include <media/rc-core.h>
#include <beep/module.h>

static struct rc_map_table lirc[] = {
	{ },
};

static struct rc_map_list lirc_map = {
	.map = {
		.scan    = lirc,
		.size    = ARRAY_SIZE(lirc),
		.rc_type = RC_TYPE_LIRC,
		.name    = RC_MAP_LIRC,
	}
};

static int __init init_rc_map_lirc(void)
{
	return rc_map_register(&lirc_map);
}

static void __exit exit_rc_map_lirc(void)
{
	rc_map_unregister(&lirc_map);
}

module_init(init_rc_map_lirc)
module_exit(exit_rc_map_lirc)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
