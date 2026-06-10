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
/* some boards require extra gpio capacity to support external
 * devices that need GPIO.
 */

#ifdef CONFIG_CPU_S3C244X
#define ARCH_NR_GPIOS	(32 * 9 + CONFIG_S3C24XX_GPIO_EXTRA)
#elif defined(CONFIG_CPU_S3C2443) || defined(CONFIG_CPU_S3C2416)
#define ARCH_NR_GPIOS	(32 * 12 + CONFIG_S3C24XX_GPIO_EXTRA)
#else
#define ARCH_NR_GPIOS	(256 + CONFIG_S3C24XX_GPIO_EXTRA)
#endif

#include <mach/gpio-nrs.h>
#include <mach/gpio-fns.h>

#ifdef CONFIG_CPU_S3C244X
#define S3C_GPIO_END	(S3C2410_GPJ(0) + 32)
#elif defined(CONFIG_CPU_S3C2443) || defined(CONFIG_CPU_S3C2416)
#define S3C_GPIO_END	(S3C2410_GPM(0) + 32)
#else
#define S3C_GPIO_END	(S3C2410_GPH(0) + 32)
#endif
