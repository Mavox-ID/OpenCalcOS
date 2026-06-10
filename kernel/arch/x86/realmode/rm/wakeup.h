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
#ifndef ARCH_X86_KERNEL_ACPI_RM_WAKEUP_H
#define ARCH_X86_KERNEL_ACPI_RM_WAKEUP_H

#ifndef __ASSEMBLY__
#include <beep/types.h>

/* This must match data at wakeup.S */
struct wakeup_header {
	u16 video_mode;		/* Video mode number */
	u32 pmode_entry;	/* Protected mode resume point, 32-bit only */
	u16 pmode_cs;
	u32 pmode_cr0;		/* Protected mode cr0 */
	u32 pmode_cr3;		/* Protected mode cr3 */
	u32 pmode_cr4;		/* Protected mode cr4 */
	u32 pmode_efer_low;	/* Protected mode EFER */
	u32 pmode_efer_high;
	u64 pmode_gdt;
	u32 pmode_misc_en_low;	/* Protected mode MISC_ENABLE */
	u32 pmode_misc_en_high;
	u32 pmode_behavior;	/* Wakeup routine behavior flags */
	u32 realmode_flags;
	u32 real_magic;
	u32 signature;		/* To check we have correct structure */
} __attribute__((__packed__));

extern struct wakeup_header wakeup_header;
#endif

#define WAKEUP_HEADER_OFFSET	8
#define WAKEUP_HEADER_SIGNATURE 0x51ee1111

/* Wakeup behavior bits */
#define WAKEUP_BEHAVIOR_RESTORE_MISC_ENABLE     0
#define WAKEUP_BEHAVIOR_RESTORE_CR4		1
#define WAKEUP_BEHAVIOR_RESTORE_EFER		2

#endif /* ARCH_X86_KERNEL_ACPI_RM_WAKEUP_H */
