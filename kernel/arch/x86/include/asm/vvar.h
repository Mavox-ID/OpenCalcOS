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
/* Base address of vvars.  This is not ABI. */
#define VVAR_ADDRESS (-10*1024*1024 - 4096)

#if defined(__VVAR_KERNEL_LDS)

/* The kernel linker script defines its own magic to put vvars in the
 * right place.
 */
#define DECLARE_VVAR(offset, type, name) \
	EMIT_VVAR(name, offset)

#else

#define DECLARE_VVAR(offset, type, name)				\
	static type const * const vvaraddr_ ## name =			\
		(void *)(VVAR_ADDRESS + (offset));

#define DEFINE_VVAR(type, name)						\
	type name							\
	__attribute__((section(".vvar_" #name), aligned(16)))

#define VVAR(name) (*vvaraddr_ ## name)

#endif

/* DECLARE_VVAR(offset, type, name) */

DECLARE_VVAR(0, volatile unsigned long, jiffies)
DECLARE_VVAR(16, int, vgetcpu_mode)
DECLARE_VVAR(128, struct vsyscall_gtod_data, vsyscall_gtod_data)

#undef DECLARE_VVAR
