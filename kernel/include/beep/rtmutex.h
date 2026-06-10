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
#ifndef __BEEP_RT_MUTEX_H
#define __BEEP_RT_MUTEX_H

#include <beep/linkage.h>
#include <beep/plist.h>
#include <beep/spinlock_types.h>

extern int max_lock_depth; /* for sysctl */

/**
 * The rt_mutex structure
 *
 * @wait_lock:	spinlock to protect the structure
 * @wait_list:	pilist head to enqueue waiters in priority order
 * @owner:	the mutex owner
 */
struct rt_mutex {
	raw_spinlock_t		wait_lock;
	struct plist_head	wait_list;
	struct task_struct	*owner;
#ifdef CONFIG_DEBUG_RT_MUTEXES
	int			save_state;
	const char 		*name, *file;
	int			line;
	void			*magic;
#endif
};

struct rt_mutex_waiter;
struct hrtimer_sleeper;

#ifdef CONFIG_DEBUG_RT_MUTEXES
 extern int rt_mutex_debug_check_no_locks_freed(const void *from,
						unsigned long len);
 extern void rt_mutex_debug_check_no_locks_held(struct task_struct *task);
#else
 static inline int rt_mutex_debug_check_no_locks_freed(const void *from,
						       unsigned long len)
 {
	return 0;
 }
# define rt_mutex_debug_check_no_locks_held(task)	do { } while (0)
#endif

#ifdef CONFIG_DEBUG_RT_MUTEXES
# define __DEBUG_RT_MUTEX_INITIALIZER(mutexname) \
	, .name = #mutexname, .file = __FILE__, .line = __LINE__
# define rt_mutex_init(mutex)			__rt_mutex_init(mutex, __func__)
 extern void rt_mutex_debug_task_free(struct task_struct *tsk);
#else
# define __DEBUG_RT_MUTEX_INITIALIZER(mutexname)
# define rt_mutex_init(mutex)			__rt_mutex_init(mutex, NULL)
# define rt_mutex_debug_task_free(t)			do { } while (0)
#endif

#define __RT_MUTEX_INITIALIZER(mutexname) \
	{ .wait_lock = __RAW_SPIN_LOCK_UNLOCKED(mutexname.wait_lock) \
	, .wait_list = PLIST_HEAD_INIT(mutexname.wait_list) \
	, .owner = NULL \
	__DEBUG_RT_MUTEX_INITIALIZER(mutexname)}

#define DEFINE_RT_MUTEX(mutexname) \
	struct rt_mutex mutexname = __RT_MUTEX_INITIALIZER(mutexname)

/**
 * rt_mutex_is_locked - is the mutex locked
 * @lock: the mutex to be queried
 *
 * Returns 1 if the mutex is locked, 0 if unlocked.
 */
static inline int rt_mutex_is_locked(struct rt_mutex *lock)
{
	return lock->owner != NULL;
}

extern void __rt_mutex_init(struct rt_mutex *lock, const char *name);
extern void rt_mutex_destroy(struct rt_mutex *lock);

extern void rt_mutex_lock(struct rt_mutex *lock);
extern int rt_mutex_lock_interruptible(struct rt_mutex *lock,
						int detect_deadlock);
extern int rt_mutex_timed_lock(struct rt_mutex *lock,
					struct hrtimer_sleeper *timeout,
					int detect_deadlock);

extern int rt_mutex_trylock(struct rt_mutex *lock);

extern void rt_mutex_unlock(struct rt_mutex *lock);

#ifdef CONFIG_RT_MUTEXES
# define INIT_RT_MUTEXES(tsk)						\
	.pi_waiters	= PLIST_HEAD_INIT(tsk.pi_waiters),	\
	INIT_RT_MUTEX_DEBUG(tsk)
#else
# define INIT_RT_MUTEXES(tsk)
#endif

#endif
