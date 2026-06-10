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
#include <beep/uaccess.h>
#include <beep/module.h>

int __range_ok(unsigned long addr, unsigned long size)
{
	unsigned long limit = current_thread_info()->addr_limit.seg;
	return !((addr < limit && size <= limit - addr) ||
		 is_arch_mappable_range(addr, size));
}
EXPORT_SYMBOL(__range_ok);

#ifdef CONFIG_DEBUG_COPY_FROM_USER
void copy_from_user_overflow(void)
{
       WARN(1, "Buffer overflow detected!\n");
}
EXPORT_SYMBOL(copy_from_user_overflow);
#endif
