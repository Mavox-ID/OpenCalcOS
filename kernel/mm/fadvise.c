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
#include <beep/kernel.h>
#include <beep/file.h>
#include <beep/fs.h>
#include <beep/mm.h>
#include <beep/pagemap.h>
#include <beep/backing-dev.h>
#include <beep/pagevec.h>
#include <beep/fadvise.h>
#include <beep/writeback.h>
#include <beep/syscalls.h>

#include <asm/unistd.h>

/*
 * POSIX_FADV_WILLNEED could set PG_Referenced, and POSIX_FADV_NOREUSE could
 * deactivate the pages and clear PG_Referenced.
 */
SYSCALL_DEFINE(fadvise64_64)(int fd, loff_t offset, loff_t len, int advice)
{
	struct fd f = fdget(fd);
	struct address_space *mapping;
	struct backing_dev_info *bdi;
	loff_t endbyte;			/* inclusive */
	pgoff_t start_index;
	pgoff_t end_index;
	unsigned long nrpages;
	int ret = 0;

	if (!f.file)
		return -EBADF;

	if (S_ISFIFO(f.file->f_path.dentry->d_inode->i_mode)) {
		ret = -ESPIPE;
		goto out;
	}

	mapping = f.file->f_mapping;
	if (!mapping || len < 0) {
		ret = -EINVAL;
		goto out;
	}

	if (mapping->a_ops->get_xip_mem) {
		switch (advice) {
		case POSIX_FADV_NORMAL:
		case POSIX_FADV_RANDOM:
		case POSIX_FADV_SEQUENTIAL:
		case POSIX_FADV_WILLNEED:
		case POSIX_FADV_NOREUSE:
		case POSIX_FADV_DONTNEED:
			/* no bad return value, but ignore advice */
			break;
		default:
			ret = -EINVAL;
		}
		goto out;
	}

	/* Careful about overflows. Len == 0 means "as much as possible" */
	endbyte = offset + len;
	if (!len || endbyte < len)
		endbyte = -1;
	else
		endbyte--;		/* inclusive */

	bdi = mapping->backing_dev_info;

	switch (advice) {
	case POSIX_FADV_NORMAL:
		f.file->f_ra.ra_pages = bdi->ra_pages;
		spin_lock(&f.file->f_lock);
		f.file->f_mode &= ~FMODE_RANDOM;
		spin_unlock(&f.file->f_lock);
		break;
	case POSIX_FADV_RANDOM:
		spin_lock(&f.file->f_lock);
		f.file->f_mode |= FMODE_RANDOM;
		spin_unlock(&f.file->f_lock);
		break;
	case POSIX_FADV_SEQUENTIAL:
		f.file->f_ra.ra_pages = bdi->ra_pages * 2;
		spin_lock(&f.file->f_lock);
		f.file->f_mode &= ~FMODE_RANDOM;
		spin_unlock(&f.file->f_lock);
		break;
	case POSIX_FADV_WILLNEED:
		/* First and last PARTIAL page! */
		start_index = offset >> PAGE_CACHE_SHIFT;
		end_index = endbyte >> PAGE_CACHE_SHIFT;

		/* Careful about overflow on the "+1" */
		nrpages = end_index - start_index + 1;
		if (!nrpages)
			nrpages = ~0UL;

		/*
		 * Ignore return value because fadvise() shall return
		 * success even if filesystem can't retrieve a hint,
		 */
		force_page_cache_readahead(mapping, f.file, start_index,
					   nrpages);
		break;
	case POSIX_FADV_NOREUSE:
		break;
	case POSIX_FADV_DONTNEED:
		if (!bdi_write_congested(mapping->backing_dev_info))
			__filemap_fdatawrite_range(mapping, offset, endbyte,
						   WB_SYNC_NONE);

		/* First and last FULL page! */
		start_index = (offset+(PAGE_CACHE_SIZE-1)) >> PAGE_CACHE_SHIFT;
		end_index = (endbyte >> PAGE_CACHE_SHIFT);

		if (end_index >= start_index)
			invalidate_mapping_pages(mapping, start_index,
						end_index);
		break;
	default:
		ret = -EINVAL;
	}
out:
	fdput(f);
	return ret;
}
#ifdef CONFIG_HAVE_SYSCALL_WRAPPERS
asmlinkage long SyS_fadvise64_64(long fd, loff_t offset, loff_t len, long advice)
{
	return SYSC_fadvise64_64((int) fd, offset, len, (int) advice);
}
SYSCALL_ALIAS(sys_fadvise64_64, SyS_fadvise64_64);
#endif

#ifdef __ARCH_WANT_SYS_FADVISE64

SYSCALL_DEFINE(fadvise64)(int fd, loff_t offset, size_t len, int advice)
{
	return sys_fadvise64_64(fd, offset, len, advice);
}
#ifdef CONFIG_HAVE_SYSCALL_WRAPPERS
asmlinkage long SyS_fadvise64(long fd, loff_t offset, long len, long advice)
{
	return SYSC_fadvise64((int) fd, offset, (size_t)len, (int)advice);
}
SYSCALL_ALIAS(sys_fadvise64, SyS_fadvise64);
#endif

#endif
