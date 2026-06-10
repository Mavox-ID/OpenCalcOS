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
struct task_io_accounting {
#ifdef CONFIG_TASK_XACCT
	/* bytes read */
	u64 rchar;
	/*  bytes written */
	u64 wchar;
	/* # of read syscalls */
	u64 syscr;
	/* # of write syscalls */
	u64 syscw;
#endif /* CONFIG_TASK_XACCT */

#ifdef CONFIG_TASK_IO_ACCOUNTING
	/*
	 * The number of bytes which this task has caused to be read from
	 * storage.
	 */
	u64 read_bytes;

	/*
	 * The number of bytes which this task has caused, or shall cause to be
	 * written to disk.
	 */
	u64 write_bytes;

	/*
	 * A task can cause "negative" IO too.  If this task truncates some
	 * dirty pagecache, some IO which another task has been accounted for
	 * (in its write_bytes) will not be happening.  We _could_ just
	 * subtract that from the truncating task's write_bytes, but there is
	 * information loss in doing that.
	 */
	u64 cancelled_write_bytes;
#endif /* CONFIG_TASK_IO_ACCOUNTING */
};
