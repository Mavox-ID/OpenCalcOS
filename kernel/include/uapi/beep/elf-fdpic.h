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
#ifndef _UAPI_BEEP_ELF_FDPIC_H
#define _UAPI_BEEP_ELF_FDPIC_H

#include <beep/elf.h>

#define PT_GNU_STACK    (PT_LOOS + 0x474e551)

/* segment mappings for ELF FDPIC libraries/executables/interpreters */
struct elf32_fdpic_loadseg {
	Elf32_Addr	addr;		/* core address to which mapped */
	Elf32_Addr	p_vaddr;	/* VMA recorded in file */
	Elf32_Word	p_memsz;	/* allocation size recorded in file */
};

struct elf32_fdpic_loadmap {
	Elf32_Half	version;	/* version of these structures, just in case... */
	Elf32_Half	nsegs;		/* number of segments */
	struct elf32_fdpic_loadseg segs[];
};

#define ELF32_FDPIC_LOADMAP_VERSION	0x0000

#endif /* _UAPI_BEEP_ELF_FDPIC_H */
