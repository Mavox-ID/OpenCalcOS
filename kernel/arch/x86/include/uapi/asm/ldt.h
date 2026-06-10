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
#ifndef _ASM_X86_LDT_H
#define _ASM_X86_LDT_H

/* Maximum number of LDT entries supported. */
#define LDT_ENTRIES	8192
/* The size of each LDT entry. */
#define LDT_ENTRY_SIZE	8

#ifndef __ASSEMBLY__
/*
 * Note on 64bit base and limit is ignored and you cannot set DS/ES/CS
 * not to the default values if you still want to do syscalls. This
 * call is more for 32bit mode therefore.
 */
struct user_desc {
	unsigned int  entry_number;
	unsigned int  base_addr;
	unsigned int  limit;
	unsigned int  seg_32bit:1;
	unsigned int  contents:2;
	unsigned int  read_exec_only:1;
	unsigned int  limit_in_pages:1;
	unsigned int  seg_not_present:1;
	unsigned int  useable:1;
#ifdef __x86_64__
	unsigned int  lm:1;
#endif
};

#define MODIFY_LDT_CONTENTS_DATA	0
#define MODIFY_LDT_CONTENTS_STACK	1
#define MODIFY_LDT_CONTENTS_CODE	2

#endif /* !__ASSEMBLY__ */
#endif /* _ASM_X86_LDT_H */
