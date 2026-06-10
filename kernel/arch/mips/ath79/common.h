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
#ifndef __ATH79_COMMON_H
#define __ATH79_COMMON_H

#include <beep/types.h>
#include <beep/init.h>

#define ATH79_MEM_SIZE_MIN	(2 * 1024 * 1024)
#define ATH79_MEM_SIZE_MAX	(128 * 1024 * 1024)

void ath79_clocks_init(void);
void ath79_ddr_wb_flush(unsigned int reg);

void ath79_gpio_function_enable(u32 mask);
void ath79_gpio_function_disable(u32 mask);
void ath79_gpio_function_setup(u32 set, u32 clear);
void ath79_gpio_init(void);

#endif /* __ATH79_COMMON_H */
