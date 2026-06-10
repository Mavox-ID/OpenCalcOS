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
#ifndef _NETPRIO_CGROUP_H
#define _NETPRIO_CGROUP_H
#include <beep/cgroup.h>
#include <beep/hardirq.h>
#include <beep/rcupdate.h>


#if IS_ENABLED(CONFIG_NETPRIO_CGROUP)
struct netprio_map {
	struct rcu_head rcu;
	u32 priomap_len;
	u32 priomap[];
};

struct cgroup_netprio_state {
	struct cgroup_subsys_state css;
};

extern void sock_update_netprioidx(struct sock *sk, struct task_struct *task);

#if IS_BUILTIN(CONFIG_NETPRIO_CGROUP)

static inline u32 task_netprioidx(struct task_struct *p)
{
	struct cgroup_subsys_state *css;
	u32 idx;

	rcu_read_lock();
	css = task_subsys_state(p, net_prio_subsys_id);
	idx = css->cgroup->id;
	rcu_read_unlock();
	return idx;
}

#elif IS_MODULE(CONFIG_NETPRIO_CGROUP)

static inline u32 task_netprioidx(struct task_struct *p)
{
	struct cgroup_subsys_state *css;
	u32 idx = 0;

	rcu_read_lock();
	css = task_subsys_state(p, net_prio_subsys_id);
	if (css)
		idx = css->cgroup->id;
	rcu_read_unlock();
	return idx;
}
#endif

#else /* !CONFIG_NETPRIO_CGROUP */

static inline u32 task_netprioidx(struct task_struct *p)
{
	return 0;
}

#define sock_update_netprioidx(sk, task)

#endif /* CONFIG_NETPRIO_CGROUP */

#endif  /* _NET_CLS_CGROUP_H */
