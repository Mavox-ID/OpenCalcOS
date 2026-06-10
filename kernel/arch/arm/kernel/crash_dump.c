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
#include <beep/crash_dump.h>
#include <beep/uaccess.h>
#include <beep/io.h>

/**
 * copy_oldmem_page() - copy one page from old kernel memory
 * @pfn: page frame number to be copied
 * @buf: buffer where the copied page is placed
 * @csize: number of bytes to copy
 * @offset: offset in bytes into the page
 * @userbuf: if set, @buf is int he user address space
 *
 * This function copies one page from old kernel memory into buffer pointed by
 * @buf. If @buf is in userspace, set @userbuf to %1. Returns number of bytes
 * copied or negative error in case of failure.
 */
ssize_t copy_oldmem_page(unsigned long pfn, char *buf,
			 size_t csize, unsigned long offset,
			 int userbuf)
{
	void *vaddr;

	if (!csize)
		return 0;

	vaddr = ioremap(pfn << PAGE_SHIFT, PAGE_SIZE);
	if (!vaddr)
		return -ENOMEM;

	if (userbuf) {
		if (copy_to_user(buf, vaddr + offset, csize)) {
			iounmap(vaddr);
			return -EFAULT;
		}
	} else {
		memcpy(buf, vaddr + offset, csize);
	}

	iounmap(vaddr);
	return csize;
}
