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
#ifndef __ASM_PREFETCH_H
#define __ASM_PREFETCH_H


/*
 * R5000 and RM5200 implements pref and prefx instructions but they're nops, so
 * rather than wasting time we pretend these processors don't support
 * prefetching at all.
 *
 * R5432 implements Load, Store, LoadStreamed, StoreStreamed, LoadRetained,
 * StoreRetained and WriteBackInvalidate but not Pref_PrepareForStore.
 *
 * Hell (and the book on my shelf I can't open ...) know what the R8000 does.
 *
 * RM7000 version 1.0 interprets all hints as Pref_Load; version 2.0 implements
 * Pref_PrepareForStore also.
 *
 * RM9000 is MIPS IV but implements prefetching like MIPS32/MIPS64; it's
 * Pref_WriteBackInvalidate is a nop and Pref_PrepareForStore is broken in
 * current versions due to erratum G105.
 *
 * VR5500 (including VR5701 and VR7701) only implement load prefetch.
 *
 * Finally MIPS32 and MIPS64 implement all of the following hints.
 */

#define Pref_Load			0
#define Pref_Store			1
						/* 2 and 3 are reserved */
#define Pref_LoadStreamed		4
#define Pref_StoreStreamed		5
#define Pref_LoadRetained		6
#define Pref_StoreRetained		7
						/* 8 ... 24 are reserved */
#define Pref_WriteBackInvalidate	25
#define Pref_PrepareForStore		30

#ifdef __ASSEMBLY__

	.macro	__pref hint addr
#ifdef CONFIG_CPU_HAS_PREFETCH
	pref	\hint, \addr
#endif
	.endm

	.macro	pref_load addr
	__pref	Pref_Load, \addr
	.endm

	.macro	pref_store addr
	__pref	Pref_Store, \addr
	.endm

	.macro	pref_load_streamed addr
	__pref	Pref_LoadStreamed, \addr
	.endm

	.macro	pref_store_streamed addr
	__pref	Pref_StoreStreamed, \addr
	.endm

	.macro	pref_load_retained addr
	__pref	Pref_LoadRetained, \addr
	.endm

	.macro	pref_store_retained addr
	__pref	Pref_StoreRetained, \addr
	.endm

	.macro	pref_wback_inv addr
	__pref	Pref_WriteBackInvalidate, \addr
	.endm

	.macro	pref_prepare_for_store addr
	__pref	Pref_PrepareForStore, \addr
	.endm

#endif

#endif /* __ASM_PREFETCH_H */
