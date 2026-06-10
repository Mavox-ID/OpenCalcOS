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
 * This must be called with lock->wait_lock held.
 */
extern void debug_mutex_lock_common(struct mutex *lock,
				    struct mutex_waiter *waiter);
extern void debug_mutex_wake_waiter(struct mutex *lock,
				    struct mutex_waiter *waiter);
extern void debug_mutex_free_waiter(struct mutex_waiter *waiter);
extern void debug_mutex_add_waiter(struct mutex *lock,
				   struct mutex_waiter *waiter,
				   struct thread_info *ti);
extern void mutex_remove_waiter(struct mutex *lock, struct mutex_waiter *waiter,
				struct thread_info *ti);
extern void debug_mutex_unlock(struct mutex *lock);
extern void debug_mutex_init(struct mutex *lock, const char *name,
			     struct lock_class_key *key);

static inline void mutex_set_owner(struct mutex *lock)
{
	lock->owner = current;
}

static inline void mutex_clear_owner(struct mutex *lock)
{
	lock->owner = NULL;
}

#define spin_lock_mutex(lock, flags)			\
	do {						\
		struct mutex *l = container_of(lock, struct mutex, wait_lock); \
							\
		DEBUG_LOCKS_WARN_ON(in_interrupt());	\
		local_irq_save(flags);			\
		arch_spin_lock(&(lock)->rlock.raw_lock);\
		DEBUG_LOCKS_WARN_ON(l->magic != l);	\
	} while (0)

#define spin_unlock_mutex(lock, flags)				\
	do {							\
		arch_spin_unlock(&(lock)->rlock.raw_lock);	\
		local_irq_restore(flags);			\
		preempt_check_resched();			\
	} while (0)
