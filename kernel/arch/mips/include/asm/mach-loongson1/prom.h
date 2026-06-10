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
#ifndef __ASM_MACH_LOONGSON1_PROM_H
#define __ASM_MACH_LOONGSON1_PROM_H

#include <beep/io.h>
#include <beep/init.h>
#include <beep/irq.h>

/* environment arguments from bootloader */
extern unsigned long memsize, highmemsize;

/* loongson-specific command line, env and memory initialization */
extern char *prom_getenv(char *name);
extern void __init prom_init_cmdline(void);

#endif /* __ASM_MACH_LOONGSON1_PROM_H */
