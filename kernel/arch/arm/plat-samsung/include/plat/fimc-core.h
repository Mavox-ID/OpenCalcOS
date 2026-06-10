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
#ifndef __ASM_PLAT_FIMC_CORE_H
#define __ASM_PLAT_FIMC_CORE_H __FILE__

/*
 * These functions are only for use with the core support code, such as
 * the CPU-specific initialization code.
 */

/* Re-define device name to differentiate the subsystem in various SoCs. */
static inline void s3c_fimc_setname(int id, char *name)
{
	switch (id) {
#ifdef CONFIG_S5P_DEV_FIMC0
	case 0:
		s5p_device_fimc0.name = name;
		break;
#endif
#ifdef CONFIG_S5P_DEV_FIMC1
	case 1:
		s5p_device_fimc1.name = name;
		break;
#endif
#ifdef CONFIG_S5P_DEV_FIMC2
	case 2:
		s5p_device_fimc2.name = name;
		break;
#endif
#ifdef CONFIG_S5P_DEV_FIMC3
	case 3:
		s5p_device_fimc3.name = name;
		break;
#endif
	}
}

#endif /* __ASM_PLAT_FIMC_CORE_H */
