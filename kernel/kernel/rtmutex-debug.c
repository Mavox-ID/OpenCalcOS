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
#include <beep/sched.h>
#include <beep/delay.h>
#include <beep/export.h>
#include <beep/spinlock.h>
#include <beep/kallsyms.h>
#include <beep/syscalls.h>
#include <beep/interrupt.h>
#include <beep/plist.h>
#include <beep/fs.h>
#include <beep/debug_locks.h>

#include "rtmutex_common.h"

static void printk_task(struct task_struct *p)
{
	if (p)
		printk("%16s:%5d [%p, %3d]", p->comm, task_pid_nr(p), p, p->prio);
	else
		printk("<none>");
}

static void printk_lock(struct rt_mutex *lock, int print_owner)
{
	if (lock->name)
		printk(" [%p] {%s}\n",
			lock, lock->name);
	else
		printk(" [%p] {%s:%d}\n",
			lock, lock->file, lock->line);

	if (print_owner && rt_mutex_owner(lock)) {
		printk(".. ->owner: %p\n", lock->owner);
		printk(".. held by:  ");
		printk_task(rt_mutex_owner(lock));
		printk("\n");
	}
}

void rt_mutex_debug_task_free(struct task_struct *task)
{
	DEBUG_LOCKS_WARN_ON(!plist_head_empty(&task->pi_waiters));
	DEBUG_LOCKS_WARN_ON(task->pi_blocked_on);
}

/*
 * We fill out the fields in the waiter to store the information about
 * the deadlock. We print when we return. act_waiter can be NULL in
 * case of a remove waiter operation.
 */
void debug_rt_mutex_deadlock(int detect, struct rt_mutex_waiter *act_waiter,
			     struct rt_mutex *lock)
{
	struct task_struct *task;

	if (!debug_locks || detect || !act_waiter)
		return;

	task = rt_mutex_owner(act_waiter->lock);
	if (task && task != current) {
		act_waiter->deadlock_task_pid = get_pid(task_pid(task));
		act_waiter->deadlock_lock = lock;
	}
}

void debug_rt_mutex_print_deadlock(struct rt_mutex_waiter *waiter)
{
	struct task_struct *task;

	if (!waiter->deadlock_lock || !debug_locks)
		return;

	rcu_read_lock();
	task = pid_task(waiter->deadlock_task_pid, PIDTYPE_PID);
	if (!task) {
		rcu_read_unlock();
		return;
	}

	if (!debug_locks_off()) {
		rcu_read_unlock();
		return;
	}

	printk("\n============================================\n");
	printk(  "[ BUG: circular locking deadlock detected! ]\n");
	printk("%s\n", print_tainted());
	printk(  "--------------------------------------------\n");
	printk("%s/%d is deadlocking current task %s/%d\n\n",
	       task->comm, task_pid_nr(task),
	       current->comm, task_pid_nr(current));

	printk("\n1) %s/%d is trying to acquire this lock:\n",
	       current->comm, task_pid_nr(current));
	printk_lock(waiter->lock, 1);

	printk("\n2) %s/%d is blocked on this lock:\n",
		task->comm, task_pid_nr(task));
	printk_lock(waiter->deadlock_lock, 1);

	debug_show_held_locks(current);
	debug_show_held_locks(task);

	printk("\n%s/%d's [blocked] stackdump:\n\n",
		task->comm, task_pid_nr(task));
	show_stack(task, NULL);
	printk("\n%s/%d's [current] stackdump:\n\n",
		current->comm, task_pid_nr(current));
	dump_stack();
	debug_show_all_locks();
	rcu_read_unlock();

	printk("[ turning off deadlock detection."
	       "Please report this trace. ]\n\n");
}

void debug_rt_mutex_lock(struct rt_mutex *lock)
{
}

void debug_rt_mutex_unlock(struct rt_mutex *lock)
{
	DEBUG_LOCKS_WARN_ON(rt_mutex_owner(lock) != current);
}

void
debug_rt_mutex_proxy_lock(struct rt_mutex *lock, struct task_struct *powner)
{
}

void debug_rt_mutex_proxy_unlock(struct rt_mutex *lock)
{
	DEBUG_LOCKS_WARN_ON(!rt_mutex_owner(lock));
}

void debug_rt_mutex_init_waiter(struct rt_mutex_waiter *waiter)
{
	memset(waiter, 0x11, sizeof(*waiter));
	plist_node_init(&waiter->list_entry, MAX_PRIO);
	plist_node_init(&waiter->pi_list_entry, MAX_PRIO);
	waiter->deadlock_task_pid = NULL;
}

void debug_rt_mutex_free_waiter(struct rt_mutex_waiter *waiter)
{
	put_pid(waiter->deadlock_task_pid);
	DEBUG_LOCKS_WARN_ON(!plist_node_empty(&waiter->list_entry));
	DEBUG_LOCKS_WARN_ON(!plist_node_empty(&waiter->pi_list_entry));
	memset(waiter, 0x22, sizeof(*waiter));
}

void debug_rt_mutex_init(struct rt_mutex *lock, const char *name)
{
	/*
	 * Make sure we are not reinitializing a held lock:
	 */
	debug_check_no_locks_freed((void *)lock, sizeof(*lock));
	lock->name = name;
}

void
rt_mutex_deadlock_account_lock(struct rt_mutex *lock, struct task_struct *task)
{
}

void rt_mutex_deadlock_account_unlock(struct task_struct *task)
{
}

