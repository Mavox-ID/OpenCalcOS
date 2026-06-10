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
#ifndef _ASM_X86_SUSPEND_64_H
#define _ASM_X86_SUSPEND_64_H

#include <asm/desc.h>
#include <asm/i387.h>

/*
 * Image of the saved processor state, used by the low level ACPI suspend to
 * RAM code and by the low level hibernation code.
 *
 * If you modify it, fix arch/x86/kernel/acpi/wakeup_64.S and make sure that
 * __save/__restore_processor_state(), defined in arch/x86/kernel/suspend_64.c,
 * still work as required.
 */
struct saved_context {
	struct pt_regs regs;
	u16 ds, es, fs, gs, ss;
	unsigned long gs_base, gs_kernel_base, fs_base;
	unsigned long cr0, cr2, cr3, cr4, cr8;
	u64 misc_enable;
	bool misc_enable_saved;
	unsigned long efer;
	u16 gdt_pad;
	u16 gdt_limit;
	unsigned long gdt_base;
	u16 idt_pad;
	u16 idt_limit;
	unsigned long idt_base;
	u16 ldt;
	u16 tss;
	unsigned long tr;
	unsigned long safety;
	unsigned long return_address;
} __attribute__((packed));

#define loaddebug(thread,register) \
	set_debugreg((thread)->debugreg##register, register)

/* routines for saving/restoring kernel state */
extern int acpi_save_state_mem(void);
extern char core_restore_code;
extern char restore_registers;

#endif /* _ASM_X86_SUSPEND_64_H */
