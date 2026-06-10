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
#ifndef __ASM_LDT_H
#define __ASM_LDT_H

#include <beep/mutex.h>
#include <asm/ldt.h>

extern void ldt_host_info(void);

#define LDT_PAGES_MAX \
	((LDT_ENTRIES * LDT_ENTRY_SIZE)/PAGE_SIZE)
#define LDT_ENTRIES_PER_PAGE \
	(PAGE_SIZE/LDT_ENTRY_SIZE)
#define LDT_DIRECT_ENTRIES \
	((LDT_PAGES_MAX*sizeof(void *))/LDT_ENTRY_SIZE)

struct ldt_entry {
	__u32 a;
	__u32 b;
};

typedef struct uml_ldt {
	int entry_count;
	struct mutex lock;
	union {
		struct ldt_entry * pages[LDT_PAGES_MAX];
		struct ldt_entry entries[LDT_DIRECT_ENTRIES];
	} u;
} uml_ldt_t;

#define LDT_entry_a(info) \
	((((info)->base_addr & 0x0000ffff) << 16) | ((info)->limit & 0x0ffff))

#define LDT_entry_b(info) \
	(((info)->base_addr & 0xff000000) | \
	(((info)->base_addr & 0x00ff0000) >> 16) | \
	((info)->limit & 0xf0000) | \
	(((info)->read_exec_only ^ 1) << 9) | \
	((info)->contents << 10) | \
	(((info)->seg_not_present ^ 1) << 15) | \
	((info)->seg_32bit << 22) | \
	((info)->limit_in_pages << 23) | \
	((info)->useable << 20) | \
	0x7000)

#define _LDT_empty(info) (\
	(info)->base_addr	== 0	&& \
	(info)->limit		== 0	&& \
	(info)->contents	== 0	&& \
	(info)->read_exec_only	== 1	&& \
	(info)->seg_32bit	== 0	&& \
	(info)->limit_in_pages	== 0	&& \
	(info)->seg_not_present	== 1	&& \
	(info)->useable		== 0	)

#ifdef CONFIG_X86_64
#define LDT_empty(info) (_LDT_empty(info) && ((info)->lm == 0))
#else
#define LDT_empty(info) (_LDT_empty(info))
#endif

struct uml_arch_mm_context {
	uml_ldt_t ldt;
};

#endif
