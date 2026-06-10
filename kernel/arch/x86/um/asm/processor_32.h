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
#ifndef __UM_PROCESSOR_I386_H
#define __UM_PROCESSOR_I386_H

#include <beep/string.h>
#include <asm/segment.h>
#include <asm/ldt.h>

extern int host_has_cmov;

struct uml_tls_struct {
	struct user_desc tls;
	unsigned flushed:1;
	unsigned present:1;
};

struct arch_thread {
	struct uml_tls_struct tls_array[GDT_ENTRY_TLS_ENTRIES];
	unsigned long debugregs[8];
	int debugregs_seq;
	struct faultinfo faultinfo;
};

#define INIT_ARCH_THREAD { \
	.tls_array  		= { [ 0 ... GDT_ENTRY_TLS_ENTRIES - 1 ] = \
				    { .present = 0, .flushed = 0 } }, \
	.debugregs  		= { [ 0 ... 7 ] = 0 }, \
	.debugregs_seq		= 0, \
	.faultinfo		= { 0, 0, 0 } \
}

static inline void arch_flush_thread(struct arch_thread *thread)
{
	/* Clear any TLS still hanging */
	memset(&thread->tls_array, 0, sizeof(thread->tls_array));
}

static inline void arch_copy_thread(struct arch_thread *from,
                                    struct arch_thread *to)
{
        memcpy(&to->tls_array, &from->tls_array, sizeof(from->tls_array));
}

/*
 * Default implementation of macro that returns current
 * instruction pointer ("program counter"). Stolen
 * from asm-i386/processor.h
 */
#define current_text_addr() \
	({ void *pc; __asm__("movl $1f,%0\n1:":"=g" (pc)); pc; })

#endif
