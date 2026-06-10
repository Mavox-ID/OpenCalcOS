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
#ifndef _ASM_RWLOCK_H
#define _ASM_RWLOCK_H

#define RW_LOCK_BIAS		 0x01000000

#ifndef CONFIG_SMP

typedef struct { unsigned long a[100]; } __dummy_lock_t;
#define __dummy_lock(lock) (*(__dummy_lock_t *)(lock))

#define RW_LOCK_BIAS_STR	"0x01000000"

#define __build_read_lock_ptr(rw, helper)				\
	do {								\
		asm volatile(						\
			"	mov	(%0),d3			\n"	\
			"	sub	1,d3			\n"	\
			"	mov	d3,(%0)			\n"	\
			"	blt	1f			\n"	\
			"	bra	2f			\n"	\
			"1:	jmp	3f			\n"	\
			"2:					\n"	\
			"	.section .text.lock,\"ax\"	\n"	\
			"3:	call	"helper"[],0		\n"	\
			"	jmp	2b			\n"	\
			"	.previous"				\
			:						\
			: "d" (rw)					\
			: "memory", "d3", "cc");			\
	} while (0)

#define __build_read_lock_const(rw, helper)				\
	do {								\
		asm volatile(						\
			"	mov	(%0),d3			\n"	\
			"	sub	1,d3			\n"	\
			"	mov	d3,(%0)			\n"	\
			"	blt	1f			\n"	\
			"	bra	2f			\n"	\
			"1:	jmp	3f			\n"	\
			"2:					\n"	\
			"	.section .text.lock,\"ax\"	\n"	\
			"3:	call	"helper"[],0		\n"	\
			"	jmp	2b			\n"	\
			"	.previous"				\
			:						\
			: "d" (rw)					\
			: "memory", "d3", "cc");			\
	} while (0)

#define __build_read_lock(rw, helper) \
	do {								\
		if (__builtin_constant_p(rw))				\
			__build_read_lock_const(rw, helper);		\
		else							\
			__build_read_lock_ptr(rw, helper);		\
	} while (0)

#define __build_write_lock_ptr(rw, helper)				\
	do {								\
		asm volatile(						\
			"	mov	(%0),d3			\n"	\
			"	sub	1,d3			\n"	\
			"	mov	d3,(%0)			\n"	\
			"	blt	1f			\n"	\
			"	bra	2f			\n"	\
			"1:	jmp	3f			\n"	\
			"2:					\n"	\
			"	.section .text.lock,\"ax\"	\n"	\
			"3:	call	"helper"[],0		\n"	\
			"	jmp	2b			\n"	\
			"	.previous"				\
			:						\
			: "d" (rw)					\
			: "memory", "d3", "cc");			\
	} while (0)

#define __build_write_lock_const(rw, helper)				\
	do {								\
		asm volatile(						\
			"	mov	(%0),d3			\n"	\
			"	sub	1,d3			\n"	\
			"	mov	d3,(%0)			\n"	\
			"	blt	1f			\n"	\
			"	bra	2f			\n"	\
			"1:	jmp	3f			\n"	\
			"2:					\n"	\
			"	.section .text.lock,\"ax\"	\n"	\
			"3:	call	"helper"[],0		\n"	\
			"	jmp	2b			\n"	\
			"	.previous"				\
			:						\
			: "d" (rw)					\
			: "memory", "d3", "cc");			\
	} while (0)

#define __build_write_lock(rw, helper)					\
	do {								\
		if (__builtin_constant_p(rw))				\
			__build_write_lock_const(rw, helper);		\
		else							\
			__build_write_lock_ptr(rw, helper);		\
	} while (0)

#endif /* CONFIG_SMP */
#endif /* _ASM_RWLOCK_H */
