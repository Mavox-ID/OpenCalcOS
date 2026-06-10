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
#ifndef _ASM_X86_SUSPEND_32_H
#define _ASM_X86_SUSPEND_32_H

#include <asm/desc.h>
#include <asm/i387.h>

/* image of the saved processor state */
struct saved_context {
	u16 es, fs, gs, ss;
	unsigned long cr0, cr2, cr3, cr4;
	u64 misc_enable;
	bool misc_enable_saved;
	struct desc_ptr gdt;
	struct desc_ptr idt;
	u16 ldt;
	u16 tss;
	unsigned long tr;
	unsigned long safety;
	unsigned long return_address;
} __attribute__((packed));

#endif /* _ASM_X86_SUSPEND_32_H */
