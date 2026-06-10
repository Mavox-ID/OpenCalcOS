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
#define spin_lock_mutex(lock, flags) \
		do { spin_lock(lock); (void)(flags); } while (0)
#define spin_unlock_mutex(lock, flags) \
		do { spin_unlock(lock); (void)(flags); } while (0)
#define mutex_remove_waiter(lock, waiter, ti) \
		__list_del((waiter)->list.prev, (waiter)->list.next)

#ifdef CONFIG_SMP
static inline void mutex_set_owner(struct mutex *lock)
{
	lock->owner = current;
}

static inline void mutex_clear_owner(struct mutex *lock)
{
	lock->owner = NULL;
}
#else
static inline void mutex_set_owner(struct mutex *lock)
{
}

static inline void mutex_clear_owner(struct mutex *lock)
{
}
#endif

#define debug_mutex_wake_waiter(lock, waiter)		do { } while (0)
#define debug_mutex_free_waiter(waiter)			do { } while (0)
#define debug_mutex_add_waiter(lock, waiter, ti)	do { } while (0)
#define debug_mutex_unlock(lock)			do { } while (0)
#define debug_mutex_init(lock, name, key)		do { } while (0)

static inline void
debug_mutex_lock_common(struct mutex *lock, struct mutex_waiter *waiter)
{
}
