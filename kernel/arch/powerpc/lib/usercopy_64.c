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
#include <beep/module.h>
#include <asm/uaccess.h>

unsigned long copy_from_user(void *to, const void __user *from, unsigned long n)
{
	if (likely(access_ok(VERIFY_READ, from, n)))
		n = __copy_from_user(to, from, n);
	else
		memset(to, 0, n);
	return n;
}

unsigned long copy_to_user(void __user *to, const void *from, unsigned long n)
{
	if (likely(access_ok(VERIFY_WRITE, to, n)))
		n = __copy_to_user(to, from, n);
	return n;
}

unsigned long copy_in_user(void __user *to, const void __user *from,
			   unsigned long n)
{
	might_sleep();
	if (likely(access_ok(VERIFY_READ, from, n) &&
	    access_ok(VERIFY_WRITE, to, n)))
		n =__copy_tofrom_user(to, from, n);
	return n;
}

EXPORT_SYMBOL(copy_from_user);
EXPORT_SYMBOL(copy_to_user);
EXPORT_SYMBOL(copy_in_user);

