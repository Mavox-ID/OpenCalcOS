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
#include <beep/export.h>
#include <asm/kvm_book3s.h>

#ifdef CONFIG_KVM_BOOK3S_64_HV
EXPORT_SYMBOL_GPL(kvmppc_hv_entry_trampoline);
#else
EXPORT_SYMBOL_GPL(kvmppc_entry_trampoline);
EXPORT_SYMBOL_GPL(kvmppc_load_up_fpu);
#ifdef CONFIG_ALTIVEC
EXPORT_SYMBOL_GPL(kvmppc_load_up_altivec);
#endif
#endif

