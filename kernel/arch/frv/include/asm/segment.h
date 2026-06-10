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
#ifndef _ASM_SEGMENT_H
#define _ASM_SEGMENT_H


#ifndef __ASSEMBLY__

typedef struct {
	unsigned long seg;
} mm_segment_t;

#define MAKE_MM_SEG(s)	((mm_segment_t) { (s) })

#ifdef CONFIG_MMU
#define USER_DS			MAKE_MM_SEG(TASK_SIZE - 1)
#define KERNEL_DS		MAKE_MM_SEG(0xdfffffffUL)
#else
#define USER_DS			MAKE_MM_SEG(memory_end)
#define KERNEL_DS		MAKE_MM_SEG(0xe0000000UL)
#endif

#define get_ds()		(KERNEL_DS)
#define get_fs()		(__current_thread_info->addr_limit)
#define segment_eq(a,b)		((a).seg == (b).seg)
#define __kernel_ds_p()		segment_eq(get_fs(), KERNEL_DS)
#define get_addr_limit()	(get_fs().seg)

#define set_fs(_x)					\
do {							\
	__current_thread_info->addr_limit = (_x);	\
} while(0)


#endif /* __ASSEMBLY__ */
#endif /* _ASM_SEGMENT_H */
