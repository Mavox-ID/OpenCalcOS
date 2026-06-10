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
#ifndef __ASM_PLAT_BACKLIGHT_H
#define __ASM_PLAT_BACKLIGHT_H __FILE__

/* samsung_bl_gpio_info - GPIO info for PWM Backlight control
 * @no:		GPIO number for PWM timer out
 * @func:	Special function of GPIO line for PWM timer
 */
struct samsung_bl_gpio_info {
	int no;
	int func;
};

extern void __init samsung_bl_set(struct samsung_bl_gpio_info *gpio_info,
	struct platform_pwm_backlight_data *bl_data);

#endif /* __ASM_PLAT_BACKLIGHT_H */
