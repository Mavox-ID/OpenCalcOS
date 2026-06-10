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
#ifndef __VM_FLAGS_X86_H
#define __VM_FLAGS_X86_H

#ifdef CONFIG_X86_32

#define VM_DATA_DEFAULT_FLAGS \
	(VM_READ | VM_WRITE | \
	((current->personality & READ_IMPLIES_EXEC) ? VM_EXEC : 0 ) | \
		 VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#else

#define VM_DATA_DEFAULT_FLAGS (VM_READ | VM_WRITE | VM_EXEC | \
	VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
#define VM_STACK_DEFAULT_FLAGS (VM_GROWSDOWN | VM_READ | VM_WRITE | \
	VM_EXEC | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#endif
#endif
