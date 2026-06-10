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
extern unsigned long h720x_gettimeoffset(void);
extern void __init h720x_init_irq(void);
extern void __init h720x_map_io(void);
extern void h720x_restart(char, const char *);

#ifdef CONFIG_ARCH_H7202
extern struct sys_timer h7202_timer;
extern void __init init_hw_h7202(void);
extern void __init h7202_init_irq(void);
extern void __init h7202_init_time(void);
#endif

#ifdef CONFIG_ARCH_H7201
extern struct sys_timer h7201_timer;
#endif
