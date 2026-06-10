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
#ifndef _ASM_C6X_SETUP_H
#define _ASM_C6X_SETUP_H

#include <uapi/asm/setup.h>

#ifndef __ASSEMBLY__
extern char c6x_command_line[COMMAND_LINE_SIZE];

extern int c6x_add_memory(phys_addr_t start, unsigned long size);

extern unsigned long ram_start;
extern unsigned long ram_end;

extern int c6x_num_cores;
extern unsigned int c6x_silicon_rev;
extern unsigned int c6x_devstat;
extern unsigned char c6x_fuse_mac[6];

extern void machine_init(unsigned long dt_ptr);
extern void time_init(void);

#endif /* !__ASSEMBLY__ */
#endif /* _ASM_C6X_SETUP_H */
