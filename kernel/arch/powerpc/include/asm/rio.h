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
#ifndef ASM_PPC_RIO_H
#define ASM_PPC_RIO_H

extern void platform_rio_init(void);
#ifdef CONFIG_FSL_RIO
extern int fsl_rio_mcheck_exception(struct pt_regs *);
#else
static inline int fsl_rio_mcheck_exception(struct pt_regs *regs) {return 0; }
#endif

#endif				/* ASM_PPC_RIO_H */
