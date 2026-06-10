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
#include <beep/rtnetlink.h>
#include <beep/notifier.h>
#include <beep/export.h>

static ATOMIC_NOTIFIER_HEAD(dcbevent_notif_chain);

int register_dcbevent_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&dcbevent_notif_chain, nb);
}
EXPORT_SYMBOL(register_dcbevent_notifier);

int unregister_dcbevent_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_unregister(&dcbevent_notif_chain, nb);
}
EXPORT_SYMBOL(unregister_dcbevent_notifier);

int call_dcbevent_notifiers(unsigned long val, void *v)
{
	return atomic_notifier_call_chain(&dcbevent_notif_chain, val, v);
}
