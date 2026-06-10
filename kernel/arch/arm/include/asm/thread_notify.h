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
#ifndef ASMARM_THREAD_NOTIFY_H
#define ASMARM_THREAD_NOTIFY_H

#ifdef __KERNEL__

#ifndef __ASSEMBLY__

#include <beep/notifier.h>
#include <asm/thread_info.h>

static inline int thread_register_notifier(struct notifier_block *n)
{
	extern struct atomic_notifier_head thread_notify_head;
	return atomic_notifier_chain_register(&thread_notify_head, n);
}

static inline void thread_unregister_notifier(struct notifier_block *n)
{
	extern struct atomic_notifier_head thread_notify_head;
	atomic_notifier_chain_unregister(&thread_notify_head, n);
}

static inline void thread_notify(unsigned long rc, struct thread_info *thread)
{
	extern struct atomic_notifier_head thread_notify_head;
	atomic_notifier_call_chain(&thread_notify_head, rc, thread);
}

#endif

/*
 * These are the reason codes for the thread notifier.
 */
#define THREAD_NOTIFY_FLUSH	0
#define THREAD_NOTIFY_EXIT	1
#define THREAD_NOTIFY_SWITCH	2
#define THREAD_NOTIFY_COPY	3

#endif
#endif
