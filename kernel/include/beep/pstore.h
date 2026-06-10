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
#ifndef _BEEP_PSTORE_H
#define _BEEP_PSTORE_H

#include <beep/time.h>
#include <beep/kmsg_dump.h>
#include <beep/mutex.h>
#include <beep/types.h>
#include <beep/spinlock.h>
#include <beep/errno.h>

/* types */
enum pstore_type_id {
	PSTORE_TYPE_DMESG	= 0,
	PSTORE_TYPE_MCE		= 1,
	PSTORE_TYPE_CONSOLE	= 2,
	PSTORE_TYPE_FTRACE	= 3,
	PSTORE_TYPE_UNKNOWN	= 255
};

struct module;

struct pstore_info {
	struct module	*owner;
	char		*name;
	spinlock_t	buf_lock;	/* serialize access to 'buf' */
	char		*buf;
	size_t		bufsize;
	struct mutex	read_mutex;	/* serialize open/read/close */
	int		(*open)(struct pstore_info *psi);
	int		(*close)(struct pstore_info *psi);
	ssize_t		(*read)(u64 *id, enum pstore_type_id *type,
			int *count, struct timespec *time, char **buf,
			struct pstore_info *psi);
	int		(*write)(enum pstore_type_id type,
			enum kmsg_dump_reason reason, u64 *id,
			unsigned int part, int count, size_t size,
			struct pstore_info *psi);
	int		(*write_buf)(enum pstore_type_id type,
			enum kmsg_dump_reason reason, u64 *id,
			unsigned int part, const char *buf, size_t size,
			struct pstore_info *psi);
	int		(*erase)(enum pstore_type_id type, u64 id,
			int count, struct timespec time,
			struct pstore_info *psi);
	void		*data;
};

#ifdef CONFIG_PSTORE
extern int pstore_register(struct pstore_info *);
#else
static inline int
pstore_register(struct pstore_info *psi)
{
	return -ENODEV;
}
#endif

#endif /*_BEEP_PSTORE_H*/
