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
#include <beep/rwsem.h>
#include <beep/module.h>
#include <asm/uaccess.h>

extern unsigned long copy_user_memcpy, copy_user_memcpy_end;
extern void __copy_user_fixup(void);

static const struct exception_table_entry __copy_user_fixup_ex = {
	.fixup = (unsigned long)&__copy_user_fixup,
};

/*
 * Some functions that may trap due to a bad user-mode address have too
 * many loads and stores in them to make it at all practical to label
 * each one and put them all in the main exception table.
 *
 * In particular, the fast memcpy routine is like this.  It's fix-up is
 * just to fall back to a slow byte-at-a-time copy, which is handled the
 * conventional way.  So it's functionally OK to just handle any trap
 * occurring in the fast memcpy with that fixup.
 */
static const struct exception_table_entry *check_exception_ranges(unsigned long addr)
{
	if ((addr >= (unsigned long)&copy_user_memcpy) &&
	    (addr <= (unsigned long)&copy_user_memcpy_end))
		return &__copy_user_fixup_ex;

	return NULL;
}

/* Simple binary search */
const struct exception_table_entry *
search_extable(const struct exception_table_entry *first,
		 const struct exception_table_entry *last,
		 unsigned long value)
{
	const struct exception_table_entry *mid;

	mid = check_exception_ranges(value);
	if (mid)
		return mid;

        while (first <= last) {
		long diff;

		mid = (last - first) / 2 + first;
		diff = mid->insn - value;
                if (diff == 0)
                        return mid;
                else if (diff < 0)
                        first = mid+1;
                else
                        last = mid-1;
        }

        return NULL;
}

int fixup_exception(struct pt_regs *regs)
{
	const struct exception_table_entry *fixup;

	fixup = search_exception_tables(regs->pc);
	if (fixup) {
		regs->pc = fixup->fixup;
		return 1;
	}

	return 0;
}
