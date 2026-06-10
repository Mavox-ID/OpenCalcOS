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
#ifndef _ASM_SH_MACHVEC_H
#define _ASM_SH_MACHVEC_H

#include <beep/types.h>
#include <beep/time.h>
#include <generated/machtypes.h>

struct sh_machine_vector {
	void (*mv_setup)(char **cmdline_p);
	const char *mv_name;

	int (*mv_irq_demux)(int irq);
	void (*mv_init_irq)(void);

#ifdef CONFIG_HAS_IOPORT
	void __iomem *(*mv_ioport_map)(unsigned long port, unsigned int size);
	void (*mv_ioport_unmap)(void __iomem *);
#endif

	int (*mv_clk_init)(void);
	int (*mv_mode_pins)(void);

	void (*mv_mem_init)(void);
	void (*mv_mem_reserve)(void);
};

extern struct sh_machine_vector sh_mv;

#define get_system_type()	sh_mv.mv_name

#define __initmv \
	__used __section(.machvec.init)

#endif /* _ASM_SH_MACHVEC_H */
