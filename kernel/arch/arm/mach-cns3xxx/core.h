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
#ifndef __CNS3XXX_CORE_H
#define __CNS3XXX_CORE_H

extern struct sys_timer cns3xxx_timer;

#ifdef CONFIG_CACHE_L2X0
void __init cns3xxx_l2x0_init(void);
#else
static inline void cns3xxx_l2x0_init(void) {}
#endif /* CONFIG_CACHE_L2X0 */

void __init cns3xxx_map_io(void);
void __init cns3xxx_init_irq(void);
void cns3xxx_power_off(void);
void cns3xxx_restart(char, const char *);

#endif /* __CNS3XXX_CORE_H */
