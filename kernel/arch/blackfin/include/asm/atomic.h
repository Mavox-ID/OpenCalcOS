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
#ifndef __ARCH_BLACKFIN_ATOMIC__
#define __ARCH_BLACKFIN_ATOMIC__

#include <asm/cmpxchg.h>

#ifdef CONFIG_SMP

#include <beep/linkage.h>

asmlinkage int __raw_uncached_fetch_asm(const volatile int *ptr);
asmlinkage int __raw_atomic_update_asm(volatile int *ptr, int value);
asmlinkage int __raw_atomic_clear_asm(volatile int *ptr, int value);
asmlinkage int __raw_atomic_set_asm(volatile int *ptr, int value);
asmlinkage int __raw_atomic_xor_asm(volatile int *ptr, int value);
asmlinkage int __raw_atomic_test_asm(const volatile int *ptr, int value);

#define atomic_read(v) __raw_uncached_fetch_asm(&(v)->counter)

#define atomic_add_return(i, v) __raw_atomic_update_asm(&(v)->counter, i)
#define atomic_sub_return(i, v) __raw_atomic_update_asm(&(v)->counter, -(i))

#define atomic_clear_mask(m, v) __raw_atomic_clear_asm(&(v)->counter, m)
#define atomic_set_mask(m, v)   __raw_atomic_set_asm(&(v)->counter, m)

#endif

#include <asm-generic/atomic.h>

#endif
