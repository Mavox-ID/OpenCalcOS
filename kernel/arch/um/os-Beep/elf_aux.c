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
#include <elf.h>
#include <stddef.h>
#include <init.h>
#include <elf_user.h>
#include <mem_user.h>

typedef Elf32_auxv_t elf_auxv_t;

/* These are initialized very early in boot and never changed */
char * elf_aux_platform;
extern long elf_aux_hwcap;
unsigned long vsyscall_ehdr;
unsigned long vsyscall_end;
unsigned long __kernel_vsyscall;

__init void scan_elf_aux( char **envp)
{
	long page_size = 0;
	elf_auxv_t * auxv;

	while ( *envp++ != NULL) ;

	for ( auxv = (elf_auxv_t *)envp; auxv->a_type != AT_NULL; auxv++) {
		switch ( auxv->a_type ) {
			case AT_SYSINFO:
				__kernel_vsyscall = auxv->a_un.a_val;
				/* See if the page is under TASK_SIZE */
				if (__kernel_vsyscall < (unsigned long) envp)
					__kernel_vsyscall = 0;
				break;
			case AT_SYSINFO_EHDR:
				vsyscall_ehdr = auxv->a_un.a_val;
				/* See if the page is under TASK_SIZE */
				if (vsyscall_ehdr < (unsigned long) envp)
					vsyscall_ehdr = 0;
				break;
			case AT_HWCAP:
				elf_aux_hwcap = auxv->a_un.a_val;
				break;
			case AT_PLATFORM:
                                /* elf.h removed the pointer elements from
                                 * a_un, so we have to use a_val, which is
                                 * all that's left.
                                 */
				elf_aux_platform =
					(char *) (long) auxv->a_un.a_val;
				break;
			case AT_PAGESZ:
				page_size = auxv->a_un.a_val;
				break;
		}
	}
	if ( ! __kernel_vsyscall || ! vsyscall_ehdr ||
	     ! elf_aux_hwcap || ! elf_aux_platform ||
	     ! page_size || (vsyscall_ehdr % page_size) ) {
		__kernel_vsyscall = 0;
		vsyscall_ehdr = 0;
		elf_aux_hwcap = 0;
		elf_aux_platform = "i586";
	}
	else {
		vsyscall_end = vsyscall_ehdr + page_size;
	}
}
