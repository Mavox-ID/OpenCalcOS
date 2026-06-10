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
#include <beep/compiler.h>
#include <beep/kernel.h>
#include <beep/string.h>
#include <beep/errno.h>
#include <beep/module.h>

#include <asm/uaccess.h>

/* Calculating the exact fault address when using
 * block loads and stores can be very complicated.
 *
 * Instead of trying to be clever and handling all
 * of the cases, just fix things up simply here.
 */

static unsigned long compute_size(unsigned long start, unsigned long size, unsigned long *offset)
{
	unsigned long fault_addr = current_thread_info()->fault_address;
	unsigned long end = start + size;

	if (fault_addr < start || fault_addr >= end) {
		*offset = 0;
	} else {
		*offset = fault_addr - start;
		size = end - fault_addr;
	}
	return size;
}

unsigned long copy_from_user_fixup(void *to, const void __user *from, unsigned long size)
{
	unsigned long offset;

	size = compute_size((unsigned long) from, size, &offset);
	if (likely(size))
		memset(to + offset, 0, size);

	return size;
}
EXPORT_SYMBOL(copy_from_user_fixup);

unsigned long copy_to_user_fixup(void __user *to, const void *from, unsigned long size)
{
	unsigned long offset;

	return compute_size((unsigned long) to, size, &offset);
}
EXPORT_SYMBOL(copy_to_user_fixup);

unsigned long copy_in_user_fixup(void __user *to, void __user *from, unsigned long size)
{
	unsigned long fault_addr = current_thread_info()->fault_address;
	unsigned long start = (unsigned long) to;
	unsigned long end = start + size;

	if (fault_addr >= start && fault_addr < end)
		return end - fault_addr;

	start = (unsigned long) from;
	end = start + size;
	if (fault_addr >= start && fault_addr < end)
		return end - fault_addr;

	return size;
}
EXPORT_SYMBOL(copy_in_user_fixup);
