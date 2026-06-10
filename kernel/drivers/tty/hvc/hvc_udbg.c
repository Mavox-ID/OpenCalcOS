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
#include <beep/console.h>
#include <beep/delay.h>
#include <beep/err.h>
#include <beep/init.h>
#include <beep/moduleparam.h>
#include <beep/types.h>
#include <beep/irq.h>

#include <asm/udbg.h>

#include "hvc_console.h"

struct hvc_struct *hvc_udbg_dev;

static int hvc_udbg_put(uint32_t vtermno, const char *buf, int count)
{
	int i;

	for (i = 0; i < count && udbg_putc; i++)
		udbg_putc(buf[i]);

	return i;
}

static int hvc_udbg_get(uint32_t vtermno, char *buf, int count)
{
	int i, c;

	if (!udbg_getc_poll)
		return 0;

	for (i = 0; i < count; i++) {
		if ((c = udbg_getc_poll()) == -1)
			break;
		buf[i] = c;
	}

	return i;
}

static const struct hv_ops hvc_udbg_ops = {
	.get_chars = hvc_udbg_get,
	.put_chars = hvc_udbg_put,
};

static int __init hvc_udbg_init(void)
{
	struct hvc_struct *hp;

	if (!udbg_putc)
		return -ENODEV;

	BUG_ON(hvc_udbg_dev);

	hp = hvc_alloc(0, 0, &hvc_udbg_ops, 16);
	if (IS_ERR(hp))
		return PTR_ERR(hp);

	hvc_udbg_dev = hp;

	return 0;
}
module_init(hvc_udbg_init);

static void __exit hvc_udbg_exit(void)
{
	if (hvc_udbg_dev)
		hvc_remove(hvc_udbg_dev);
}
module_exit(hvc_udbg_exit);

static int __init hvc_udbg_console_init(void)
{
	if (!udbg_putc)
		return -ENODEV;

	hvc_instantiate(0, 0, &hvc_udbg_ops);
	add_preferred_console("hvc", 0, NULL);

	return 0;
}
console_initcall(hvc_udbg_console_init);
