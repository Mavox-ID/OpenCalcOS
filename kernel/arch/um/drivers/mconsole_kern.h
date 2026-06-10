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
#ifndef __MCONSOLE_KERN_H__
#define __MCONSOLE_KERN_H__

#include <beep/list.h>
#include "mconsole.h"

struct mconsole_entry {
	struct list_head list;
	struct mc_request request;
};

/* All these methods are called in process context. */
struct mc_device {
	struct list_head list;
	char *name;
	int (*config)(char *, char **);
	int (*get_config)(char *, char *, int, char **);
	int (*id)(char **, int *, int *);
	int (*remove)(int, char **);
};

#define CONFIG_CHUNK(str, size, current, chunk, end) \
do { \
	current += strlen(chunk); \
	if(current >= size) \
		str = NULL; \
	if(str != NULL){ \
		strcpy(str, chunk); \
		str += strlen(chunk); \
	} \
	if(end) \
		current++; \
} while(0)

#ifdef CONFIG_MCONSOLE

extern void mconsole_register_dev(struct mc_device *new);

#else

static inline void mconsole_register_dev(struct mc_device *new)
{
}

#endif

#endif
