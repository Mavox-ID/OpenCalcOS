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
#ifndef _BEEP_KOBJECT_NS_H
#define _BEEP_KOBJECT_NS_H

struct sock;
struct kobject;

/*
 * Namespace types which are used to tag kobjects and sysfs entries.
 * Network namespace will likely be the first.
 */
enum kobj_ns_type {
	KOBJ_NS_TYPE_NONE = 0,
	KOBJ_NS_TYPE_NET,
	KOBJ_NS_TYPES
};

/*
 * Callbacks so sysfs can determine namespaces
 *   @grab_current_ns: return a new reference to calling task's namespace
 *   @netlink_ns: return namespace to which a sock belongs (right?)
 *   @initial_ns: return the initial namespace (i.e. init_net_ns)
 *   @drop_ns: drops a reference to namespace
 */
struct kobj_ns_type_operations {
	enum kobj_ns_type type;
	void *(*grab_current_ns)(void);
	const void *(*netlink_ns)(struct sock *sk);
	const void *(*initial_ns)(void);
	void (*drop_ns)(void *);
};

int kobj_ns_type_register(const struct kobj_ns_type_operations *ops);
int kobj_ns_type_registered(enum kobj_ns_type type);
const struct kobj_ns_type_operations *kobj_child_ns_ops(struct kobject *parent);
const struct kobj_ns_type_operations *kobj_ns_ops(struct kobject *kobj);

void *kobj_ns_grab_current(enum kobj_ns_type type);
const void *kobj_ns_netlink(enum kobj_ns_type type, struct sock *sk);
const void *kobj_ns_initial(enum kobj_ns_type type);
void kobj_ns_drop(enum kobj_ns_type type, void *ns);

#endif /* _BEEP_KOBJECT_NS_H */
