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
#include <beep/errno.h>
#include <beep/list.h>
#include <beep/spinlock.h>
#include <beep/module.h>
#include <asm/unwinder.h>
#include <beep/atomic.h>

/*
 * This is the most basic stack unwinder an architecture can
 * provide. For architectures without reliable frame pointers, e.g.
 * RISC CPUs, it can be implemented by looking through the stack for
 * addresses that lie within the kernel text section.
 *
 * Other CPUs, e.g. x86, can use their frame pointer register to
 * construct more accurate stack traces.
 */
static struct list_head unwinder_list;
static struct unwinder stack_reader = {
	.name = "stack-reader",
	.dump = stack_reader_dump,
	.rating = 50,
	.list = {
		.next = &unwinder_list,
		.prev = &unwinder_list,
	},
};

/*
 * "curr_unwinder" points to the stack unwinder currently in use. This
 * is the unwinder with the highest rating.
 *
 * "unwinder_list" is a linked-list of all available unwinders, sorted
 * by rating.
 *
 * All modifications of "curr_unwinder" and "unwinder_list" must be
 * performed whilst holding "unwinder_lock".
 */
static struct unwinder *curr_unwinder = &stack_reader;

static struct list_head unwinder_list = {
	.next = &stack_reader.list,
	.prev = &stack_reader.list,
};

static DEFINE_SPINLOCK(unwinder_lock);

/**
 * select_unwinder - Select the best registered stack unwinder.
 *
 * Private function. Must hold unwinder_lock when called.
 *
 * Select the stack unwinder with the best rating. This is useful for
 * setting up curr_unwinder.
 */
static struct unwinder *select_unwinder(void)
{
	struct unwinder *best;

	if (list_empty(&unwinder_list))
		return NULL;

	best = list_entry(unwinder_list.next, struct unwinder, list);
	if (best == curr_unwinder)
		return NULL;

	return best;
}

/*
 * Enqueue the stack unwinder sorted by rating.
 */
static int unwinder_enqueue(struct unwinder *ops)
{
	struct list_head *tmp, *entry = &unwinder_list;

	list_for_each(tmp, &unwinder_list) {
		struct unwinder *o;

		o = list_entry(tmp, struct unwinder, list);
		if (o == ops)
			return -EBUSY;
		/* Keep track of the place, where to insert */
		if (o->rating >= ops->rating)
			entry = tmp;
	}
	list_add(&ops->list, entry);

	return 0;
}

/**
 * unwinder_register - Used to install new stack unwinder
 * @u: unwinder to be registered
 *
 * Install the new stack unwinder on the unwinder list, which is sorted
 * by rating.
 *
 * Returns -EBUSY if registration fails, zero otherwise.
 */
int unwinder_register(struct unwinder *u)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&unwinder_lock, flags);
	ret = unwinder_enqueue(u);
	if (!ret)
		curr_unwinder = select_unwinder();
	spin_unlock_irqrestore(&unwinder_lock, flags);

	return ret;
}

int unwinder_faulted = 0;

/*
 * Unwind the call stack and pass information to the stacktrace_ops
 * functions. Also handle the case where we need to switch to a new
 * stack dumper because the current one faulted unexpectedly.
 */
void unwind_stack(struct task_struct *task, struct pt_regs *regs,
		  unsigned long *sp, const struct stacktrace_ops *ops,
		  void *data)
{
	unsigned long flags;

	/*
	 * The problem with unwinders with high ratings is that they are
	 * inherently more complicated than the simple ones with lower
	 * ratings. We are therefore more likely to fault in the
	 * complicated ones, e.g. hitting BUG()s. If we fault in the
	 * code for the current stack unwinder we try to downgrade to
	 * one with a lower rating.
	 *
	 * Hopefully this will give us a semi-reliable stacktrace so we
	 * can diagnose why curr_unwinder->dump() faulted.
	 */
	if (unwinder_faulted) {
		spin_lock_irqsave(&unwinder_lock, flags);

		/* Make sure no one beat us to changing the unwinder */
		if (unwinder_faulted && !list_is_singular(&unwinder_list)) {
			list_del(&curr_unwinder->list);
			curr_unwinder = select_unwinder();

			unwinder_faulted = 0;
		}

		spin_unlock_irqrestore(&unwinder_lock, flags);
	}

	curr_unwinder->dump(task, regs, sp, ops, data);
}
EXPORT_SYMBOL_GPL(unwind_stack);
