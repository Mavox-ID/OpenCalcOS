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
#ifndef _ASM_IA64_SN_SIMULATOR_H
#define _ASM_IA64_SN_SIMULATOR_H

#if defined(CONFIG_IA64_GENERIC) || defined(CONFIG_IA64_SGI_SN2) || defined(CONFIG_IA64_SGI_UV)
#define SNMAGIC 0xaeeeeeee8badbeefL
#define IS_MEDUSA()			({long sn; asm("mov %0=cpuid[%1]" : "=r"(sn) : "r"(2)); sn == SNMAGIC;})

#define SIMULATOR_SLEEP()		asm("nop.i 0x8beef")
#define IS_RUNNING_ON_SIMULATOR()	(sn_prom_type)
#define IS_RUNNING_ON_FAKE_PROM()	(sn_prom_type == 2)
extern int sn_prom_type;		/* 0=hardware, 1=medusa/realprom, 2=medusa/fakeprom */
#else
#define IS_MEDUSA()			0
#define SIMULATOR_SLEEP()
#define IS_RUNNING_ON_SIMULATOR()	0
#endif

#endif /* _ASM_IA64_SN_SIMULATOR_H */
