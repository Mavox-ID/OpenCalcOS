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
#ifndef _ARCH_X86_KERNEL_TLS_H

#include <beep/regset.h>

extern user_regset_active_fn regset_tls_active;
extern user_regset_get_fn regset_tls_get;
extern user_regset_set_fn regset_tls_set;

#endif	/* _ARCH_X86_KERNEL_TLS_H */
