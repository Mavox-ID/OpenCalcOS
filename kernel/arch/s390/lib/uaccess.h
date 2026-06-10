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
#ifndef __ARCH_S390_LIB_UACCESS_H
#define __ARCH_S390_LIB_UACCESS_H

extern size_t copy_from_user_std(size_t, const void __user *, void *);
extern size_t copy_to_user_std(size_t, void __user *, const void *);
extern size_t strnlen_user_std(size_t, const char __user *);
extern size_t strncpy_from_user_std(size_t, const char __user *, char *);
extern int futex_atomic_cmpxchg_std(u32 *, u32 __user *, u32, u32);
extern int futex_atomic_op_std(int, u32 __user *, int, int *);

extern size_t copy_from_user_pt(size_t, const void __user *, void *);
extern size_t copy_to_user_pt(size_t, void __user *, const void *);
extern int futex_atomic_op_pt(int, u32 __user *, int, int *);
extern int futex_atomic_cmpxchg_pt(u32 *, u32 __user *, u32, u32);

#endif /* __ARCH_S390_LIB_UACCESS_H */
