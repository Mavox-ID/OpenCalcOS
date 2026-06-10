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
#ifndef _ASM_POWERPC_DEBUG_H
#define _ASM_POWERPC_DEBUG_H

struct pt_regs;

extern struct dentry *powerpc_debugfs_root;

#if defined(CONFIG_DEBUGGER) || defined(CONFIG_KEXEC)

extern int (*__debugger)(struct pt_regs *regs);
extern int (*__debugger_ipi)(struct pt_regs *regs);
extern int (*__debugger_bpt)(struct pt_regs *regs);
extern int (*__debugger_sstep)(struct pt_regs *regs);
extern int (*__debugger_iabr_match)(struct pt_regs *regs);
extern int (*__debugger_dabr_match)(struct pt_regs *regs);
extern int (*__debugger_fault_handler)(struct pt_regs *regs);

#define DEBUGGER_BOILERPLATE(__NAME) \
static inline int __NAME(struct pt_regs *regs) \
{ \
	if (unlikely(__ ## __NAME)) \
		return __ ## __NAME(regs); \
	return 0; \
}

DEBUGGER_BOILERPLATE(debugger)
DEBUGGER_BOILERPLATE(debugger_ipi)
DEBUGGER_BOILERPLATE(debugger_bpt)
DEBUGGER_BOILERPLATE(debugger_sstep)
DEBUGGER_BOILERPLATE(debugger_iabr_match)
DEBUGGER_BOILERPLATE(debugger_dabr_match)
DEBUGGER_BOILERPLATE(debugger_fault_handler)

#else
static inline int debugger(struct pt_regs *regs) { return 0; }
static inline int debugger_ipi(struct pt_regs *regs) { return 0; }
static inline int debugger_bpt(struct pt_regs *regs) { return 0; }
static inline int debugger_sstep(struct pt_regs *regs) { return 0; }
static inline int debugger_iabr_match(struct pt_regs *regs) { return 0; }
static inline int debugger_dabr_match(struct pt_regs *regs) { return 0; }
static inline int debugger_fault_handler(struct pt_regs *regs) { return 0; }
#endif

extern int set_dabr(unsigned long dabr, unsigned long dabrx);
#ifdef CONFIG_PPC_ADV_DEBUG_REGS
extern void do_send_trap(struct pt_regs *regs, unsigned long address,
			 unsigned long error_code, int signal_code, int brkpt);
#else
extern void do_dabr(struct pt_regs *regs, unsigned long address,
		    unsigned long error_code);
#endif

#endif /* _ASM_POWERPC_DEBUG_H */
