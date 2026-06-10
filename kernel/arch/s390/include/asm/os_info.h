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
#ifndef _ASM_S390_OS_INFO_H
#define _ASM_S390_OS_INFO_H

#define OS_INFO_VERSION_MAJOR	1
#define OS_INFO_VERSION_MINOR	1
#define OS_INFO_MAGIC		0x4f53494e464f535aULL /* OSINFOSZ */

#define OS_INFO_VMCOREINFO	0
#define OS_INFO_REIPL_BLOCK	1

struct os_info_entry {
	u64	addr;
	u64	size;
	u32	csum;
} __packed;

struct os_info {
	u64	magic;
	u32	csum;
	u16	version_major;
	u16	version_minor;
	u64	crashkernel_addr;
	u64	crashkernel_size;
	struct os_info_entry entry[2];
	u8	reserved[4024];
} __packed;

void os_info_init(void);
void os_info_entry_add(int nr, void *ptr, u64 len);
void os_info_crashkernel_add(unsigned long base, unsigned long size);
u32 os_info_csum(struct os_info *os_info);

#ifdef CONFIG_CRASH_DUMP
void *os_info_old_entry(int nr, unsigned long *size);
int copy_from_oldmem(void *dest, void *src, size_t count);
#else
static inline void *os_info_old_entry(int nr, unsigned long *size)
{
	return NULL;
}
#endif

#endif /* _ASM_S390_OS_INFO_H */
