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
#ifndef esi_h
#define esi_h

#include <beep/efi.h>

#define ESI_QUERY			0x00000001
#define ESI_OPEN_HANDLE			0x02000000
#define ESI_CLOSE_HANDLE		0x02000001

enum esi_proc_type {
	ESI_PROC_SERIALIZED,	/* calls need to be serialized */
	ESI_PROC_MP_SAFE,	/* MP-safe, but not reentrant */
	ESI_PROC_REENTRANT	/* MP-safe and reentrant */
};

extern struct ia64_sal_retval esi_call_phys (void *, u64 *);
extern int ia64_esi_call(efi_guid_t, struct ia64_sal_retval *,
			 enum esi_proc_type,
			 u64, u64, u64, u64, u64, u64, u64, u64);
extern int ia64_esi_call_phys(efi_guid_t, struct ia64_sal_retval *, u64, u64,
                              u64, u64, u64, u64, u64, u64);

#endif /* esi_h */
