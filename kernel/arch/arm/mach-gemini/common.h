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
#ifndef __GEMINI_COMMON_H__
#define __GEMINI_COMMON_H__

struct mtd_partition;

extern void gemini_map_io(void);
extern void gemini_init_irq(void);
extern void gemini_timer_init(void);
extern void gemini_gpio_init(void);
extern void platform_register_rtc(void);

/* Common platform devices registration functions */
extern int platform_register_uart(void);
extern int platform_register_pflash(unsigned int size,
				    struct mtd_partition *parts,
				    unsigned int nr_parts);

#endif /* __GEMINI_COMMON_H__ */
