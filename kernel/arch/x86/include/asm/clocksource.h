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
#ifndef _ASM_X86_CLOCKSOURCE_H
#define _ASM_X86_CLOCKSOURCE_H

#ifdef CONFIG_X86_64

#define VCLOCK_NONE 0  /* No vDSO clock available.	*/
#define VCLOCK_TSC  1  /* vDSO should use vread_tsc.	*/
#define VCLOCK_HPET 2  /* vDSO should use vread_hpet.	*/
#define VCLOCK_PVCLOCK 3 /* vDSO should use vread_pvclock. */

struct arch_clocksource_data {
	int vclock_mode;
};

#endif /* CONFIG_X86_64 */

#endif /* _ASM_X86_CLOCKSOURCE_H */
