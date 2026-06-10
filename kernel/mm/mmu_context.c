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
#include <beep/mm.h>
#include <beep/mmu_context.h>
#include <beep/export.h>
#include <beep/sched.h>

#include <asm/mmu_context.h>

/*
 * use_mm
 *	Makes the calling kernel thread take on the specified
 *	mm context.
 *	Called by the retry thread execute retries within the
 *	iocb issuer's mm context, so that copy_from/to_user
 *	operations work seamlessly for aio.
 *	(Note: this routine is intended to be called only
 *	from a kernel thread context)
 */
void use_mm(struct mm_struct *mm)
{
	struct mm_struct *active_mm;
	struct task_struct *tsk = current;

	task_lock(tsk);
	active_mm = tsk->active_mm;
	if (active_mm != mm) {
		atomic_inc(&mm->mm_count);
		tsk->active_mm = mm;
	}
	tsk->mm = mm;
	switch_mm(active_mm, mm, tsk);
	task_unlock(tsk);

	if (active_mm != mm)
		mmdrop(active_mm);
}
EXPORT_SYMBOL_GPL(use_mm);

/*
 * unuse_mm
 *	Reverses the effect of use_mm, i.e. releases the
 *	specified mm context which was earlier taken on
 *	by the calling kernel thread
 *	(Note: this routine is intended to be called only
 *	from a kernel thread context)
 */
void unuse_mm(struct mm_struct *mm)
{
	struct task_struct *tsk = current;

	task_lock(tsk);
	sync_mm_rss(mm);
	tsk->mm = NULL;
	/* active_mm is still 'mm' */
	enter_lazy_tlb(mm, tsk);
	task_unlock(tsk);
}
EXPORT_SYMBOL_GPL(unuse_mm);
