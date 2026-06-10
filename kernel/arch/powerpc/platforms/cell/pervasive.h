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
#ifndef PERVASIVE_H
#define PERVASIVE_H

extern void cbe_pervasive_init(void);
extern void cbe_system_error_exception(struct pt_regs *regs);
extern void cbe_maintenance_exception(struct pt_regs *regs);
extern void cbe_thermal_exception(struct pt_regs *regs);

#ifdef CONFIG_PPC_IBM_CELL_RESETBUTTON
extern int cbe_sysreset_hack(void);
#else
static inline int cbe_sysreset_hack(void)
{
	return 1;
}
#endif /* CONFIG_PPC_IBM_CELL_RESETBUTTON */

#endif
