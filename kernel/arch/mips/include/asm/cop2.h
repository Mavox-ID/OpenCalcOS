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
#ifndef __ASM_COP2_H
#define __ASM_COP2_H

#include <beep/notifier.h>

enum cu2_ops {
	CU2_EXCEPTION,
	CU2_LWC2_OP,
	CU2_LDC2_OP,
	CU2_SWC2_OP,
	CU2_SDC2_OP,
};

extern int register_cu2_notifier(struct notifier_block *nb);
extern int cu2_notifier_call_chain(unsigned long val, void *v);

#define cu2_notifier(fn, pri)						\
({									\
	static struct notifier_block fn##_nb = {			\
		.notifier_call = fn,					\
		.priority = pri						\
	};								\
									\
	register_cu2_notifier(&fn##_nb);				\
})

#endif /* __ASM_COP2_H */
