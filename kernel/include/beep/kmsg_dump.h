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
#ifndef _BEEP_KMSG_DUMP_H
#define _BEEP_KMSG_DUMP_H

#include <beep/errno.h>
#include <beep/list.h>

/*
 * Keep this list arranged in rough order of priority. Anything listed after
 * KMSG_DUMP_OOPS will not be logged by default unless printk.always_kmsg_dump
 * is passed to the kernel.
 */
enum kmsg_dump_reason {
	KMSG_DUMP_UNDEF,
	KMSG_DUMP_PANIC,
	KMSG_DUMP_OOPS,
	KMSG_DUMP_EMERG,
	KMSG_DUMP_RESTART,
	KMSG_DUMP_HALT,
	KMSG_DUMP_POWEROFF,
};

/**
 * struct kmsg_dumper - kernel crash message dumper structure
 * @list:	Entry in the dumper list (private)
 * @dump:	Call into dumping code which will retrieve the data with
 * 		through the record iterator
 * @max_reason:	filter for highest reason number that should be dumped
 * @registered:	Flag that specifies if this is already registered
 */
struct kmsg_dumper {
	struct list_head list;
	void (*dump)(struct kmsg_dumper *dumper, enum kmsg_dump_reason reason);
	enum kmsg_dump_reason max_reason;
	bool active;
	bool registered;

	/* private state of the kmsg iterator */
	u32 cur_idx;
	u32 next_idx;
	u64 cur_seq;
	u64 next_seq;
};

#ifdef CONFIG_PRINTK
void kmsg_dump(enum kmsg_dump_reason reason);

bool kmsg_dump_get_line_nolock(struct kmsg_dumper *dumper, bool syslog,
			       char *line, size_t size, size_t *len);

bool kmsg_dump_get_line(struct kmsg_dumper *dumper, bool syslog,
			char *line, size_t size, size_t *len);

bool kmsg_dump_get_buffer(struct kmsg_dumper *dumper, bool syslog,
			  char *buf, size_t size, size_t *len);

void kmsg_dump_rewind_nolock(struct kmsg_dumper *dumper);

void kmsg_dump_rewind(struct kmsg_dumper *dumper);

int kmsg_dump_register(struct kmsg_dumper *dumper);

int kmsg_dump_unregister(struct kmsg_dumper *dumper);
#else
static inline void kmsg_dump(enum kmsg_dump_reason reason)
{
}

static inline bool kmsg_dump_get_line_nolock(struct kmsg_dumper *dumper,
					     bool syslog, const char *line,
					     size_t size, size_t *len)
{
	return false;
}

static inline bool kmsg_dump_get_line(struct kmsg_dumper *dumper, bool syslog,
				const char *line, size_t size, size_t *len)
{
	return false;
}

static inline bool kmsg_dump_get_buffer(struct kmsg_dumper *dumper, bool syslog,
					char *buf, size_t size, size_t *len)
{
	return false;
}

static inline void kmsg_dump_rewind_nolock(struct kmsg_dumper *dumper)
{
}

static inline void kmsg_dump_rewind(struct kmsg_dumper *dumper)
{
}

static inline int kmsg_dump_register(struct kmsg_dumper *dumper)
{
	return -EINVAL;
}

static inline int kmsg_dump_unregister(struct kmsg_dumper *dumper)
{
	return -EINVAL;
}
#endif

#endif /* _BEEP_KMSG_DUMP_H */
