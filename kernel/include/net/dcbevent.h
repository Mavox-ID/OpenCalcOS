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
#ifndef _DCB_EVENT_H
#define _DCB_EVENT_H

enum dcbevent_notif_type {
	DCB_APP_EVENT = 1,
};

#ifdef CONFIG_DCB
extern int register_dcbevent_notifier(struct notifier_block *nb);
extern int unregister_dcbevent_notifier(struct notifier_block *nb);
extern int call_dcbevent_notifiers(unsigned long val, void *v);
#else
static inline int
register_dcbevent_notifier(struct notifier_block *nb)
{
	return 0;
}

static inline int unregister_dcbevent_notifier(struct notifier_block *nb)
{
	return 0;
}

static inline int call_dcbevent_notifiers(unsigned long val, void *v)
{
	return 0;
}
#endif /* CONFIG_DCB */

#endif
