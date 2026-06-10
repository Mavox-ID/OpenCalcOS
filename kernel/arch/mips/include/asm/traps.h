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
#ifndef _ASM_TRAPS_H
#define _ASM_TRAPS_H

/*
 * Possible status responses for a board_be_handler backend.
 */
#define MIPS_BE_DISCARD	0		/* return with no action */
#define MIPS_BE_FIXUP	1		/* return to the fixup code */
#define MIPS_BE_FATAL	2		/* treat as an unrecoverable error */

extern void (*board_be_init)(void);
extern int (*board_be_handler)(struct pt_regs *regs, int is_fixup);

extern void (*board_nmi_handler_setup)(void);
extern void (*board_ejtag_handler_setup)(void);
extern void (*board_bind_eic_interrupt)(int irq, int regset);
extern void (*board_ebase_setup)(void);
extern void (*board_cache_error_setup)(void);

extern int register_nmi_notifier(struct notifier_block *nb);

#define nmi_notifier(fn, pri)						\
({									\
	static struct notifier_block fn##_nb = {			\
		.notifier_call = fn,					\
		.priority = pri						\
	};								\
									\
	register_nmi_notifier(&fn##_nb);				\
})

#endif /* _ASM_TRAPS_H */
