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
extern void
rt_mutex_deadlock_account_lock(struct rt_mutex *lock, struct task_struct *task);
extern void rt_mutex_deadlock_account_unlock(struct task_struct *task);
extern void debug_rt_mutex_init_waiter(struct rt_mutex_waiter *waiter);
extern void debug_rt_mutex_free_waiter(struct rt_mutex_waiter *waiter);
extern void debug_rt_mutex_init(struct rt_mutex *lock, const char *name);
extern void debug_rt_mutex_lock(struct rt_mutex *lock);
extern void debug_rt_mutex_unlock(struct rt_mutex *lock);
extern void debug_rt_mutex_proxy_lock(struct rt_mutex *lock,
				      struct task_struct *powner);
extern void debug_rt_mutex_proxy_unlock(struct rt_mutex *lock);
extern void debug_rt_mutex_deadlock(int detect, struct rt_mutex_waiter *waiter,
				    struct rt_mutex *lock);
extern void debug_rt_mutex_print_deadlock(struct rt_mutex_waiter *waiter);
# define debug_rt_mutex_reset_waiter(w)			\
	do { (w)->deadlock_lock = NULL; } while (0)

static inline int debug_rt_mutex_detect_deadlock(struct rt_mutex_waiter *waiter,
						 int detect)
{
	return (waiter != NULL);
}
