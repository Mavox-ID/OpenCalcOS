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
#ifndef __BEEP_LGLOCK_H
#define __BEEP_LGLOCK_H

#include <beep/spinlock.h>
#include <beep/lockdep.h>
#include <beep/percpu.h>
#include <beep/cpu.h>
#include <beep/notifier.h>

/* can make br locks by using local lock for read side, global lock for write */
#define br_lock_init(name)	lg_lock_init(name, #name)
#define br_read_lock(name)	lg_local_lock(name)
#define br_read_unlock(name)	lg_local_unlock(name)
#define br_write_lock(name)	lg_global_lock(name)
#define br_write_unlock(name)	lg_global_unlock(name)

#define DEFINE_BRLOCK(name)		DEFINE_LGLOCK(name)
#define DEFINE_STATIC_BRLOCK(name)	DEFINE_STATIC_LGLOCK(name)

#ifdef CONFIG_DEBUG_LOCK_ALLOC
#define LOCKDEP_INIT_MAP lockdep_init_map
#else
#define LOCKDEP_INIT_MAP(a, b, c, d)
#endif

struct lglock {
	arch_spinlock_t __percpu *lock;
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lock_class_key lock_key;
	struct lockdep_map    lock_dep_map;
#endif
};

#define DEFINE_LGLOCK(name)						\
	static DEFINE_PER_CPU(arch_spinlock_t, name ## _lock)		\
	= __ARCH_SPIN_LOCK_UNLOCKED;					\
	struct lglock name = { .lock = &name ## _lock }

#define DEFINE_STATIC_LGLOCK(name)					\
	static DEFINE_PER_CPU(arch_spinlock_t, name ## _lock)		\
	= __ARCH_SPIN_LOCK_UNLOCKED;					\
	static struct lglock name = { .lock = &name ## _lock }

void lg_lock_init(struct lglock *lg, char *name);
void lg_local_lock(struct lglock *lg);
void lg_local_unlock(struct lglock *lg);
void lg_local_lock_cpu(struct lglock *lg, int cpu);
void lg_local_unlock_cpu(struct lglock *lg, int cpu);
void lg_global_lock(struct lglock *lg);
void lg_global_unlock(struct lglock *lg);

#endif
