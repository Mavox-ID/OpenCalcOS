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
#ifndef _MIPS_KEXEC
# define _MIPS_KEXEC

#include <asm/stacktrace.h>

/* Maximum physical address we can use pages from */
#define KEXEC_SOURCE_MEMORY_LIMIT (0x20000000)
/* Maximum address we can reach in physical address mode */
#define KEXEC_DESTINATION_MEMORY_LIMIT (0x20000000)
 /* Maximum address we can use for the control code buffer */
#define KEXEC_CONTROL_MEMORY_LIMIT (0x20000000)
/* Reserve 3*4096 bytes for board-specific info */
#define KEXEC_CONTROL_PAGE_SIZE (4096 + 3*4096)

/* The native architecture */
#define KEXEC_ARCH KEXEC_ARCH_MIPS
#define MAX_NOTE_BYTES 1024

static inline void crash_setup_regs(struct pt_regs *newregs,
				    struct pt_regs *oldregs)
{
	if (oldregs)
		memcpy(newregs, oldregs, sizeof(*newregs));
	else
		prepare_frametrace(newregs);
}

#ifdef CONFIG_KEXEC
struct kimage;
extern unsigned long kexec_args[4];
extern int (*_machine_kexec_prepare)(struct kimage *);
extern void (*_machine_kexec_shutdown)(void);
extern void (*_machine_crash_shutdown)(struct pt_regs *regs);
extern void default_machine_crash_shutdown(struct pt_regs *regs);
#ifdef CONFIG_SMP
extern const unsigned char kexec_smp_wait[];
extern unsigned long secondary_kexec_args[4];
extern void (*relocated_kexec_smp_wait) (void *);
extern atomic_t kexec_ready_to_reboot;
#endif
#endif

#endif /* !_MIPS_KEXEC */
