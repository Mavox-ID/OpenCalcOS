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
#include <beep/fb.h>
#include <beep/notifier.h>
#include <beep/export.h>

static BLOCKING_NOTIFIER_HEAD(fb_notifier_list);

/**
 *	fb_register_client - register a client notifier
 *	@nb: notifier block to callback on events
 */
int fb_register_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&fb_notifier_list, nb);
}
EXPORT_SYMBOL(fb_register_client);

/**
 *	fb_unregister_client - unregister a client notifier
 *	@nb: notifier block to callback on events
 */
int fb_unregister_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&fb_notifier_list, nb);
}
EXPORT_SYMBOL(fb_unregister_client);

/**
 * fb_notifier_call_chain - notify clients of fb_events
 *
 */
int fb_notifier_call_chain(unsigned long val, void *v)
{
	return blocking_notifier_call_chain(&fb_notifier_list, val, v);
}
EXPORT_SYMBOL_GPL(fb_notifier_call_chain);
