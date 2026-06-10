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

/*
 * Mostly copied from i386/x86_86 - eliminated the eip < PAGE_OFFSET because
 * that's not relevant in skas mode.
 */

int is_valid_bugaddr(unsigned long eip)
{
	unsigned short ud2;

	if (probe_kernel_address((unsigned short __user *)eip, ud2))
		return 0;

	return ud2 == 0x0b0f;
}
