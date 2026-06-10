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
#ifndef __ASM_PLAT_FB_CORE_H
#define __ASM_PLAT_FB_CORE_H __FILE__

/*
 * These functions are only for use with the core support code, such as
 * the CPU-specific initialization code.
 */

/* Re-define device name depending on support. */
static inline void s3c_fb_setname(char *name)
{
#ifdef CONFIG_S3C_DEV_FB
	s3c_device_fb.name = name;
#endif
}

/* Re-define device name depending on support. */
static inline void s5p_fb_setname(int id, char *name)
{
	switch (id) {
#ifdef CONFIG_S5P_DEV_FIMD0
	case 0:
		s5p_device_fimd0.name = name;
	break;
#endif
	default:
		printk(KERN_ERR "%s: invalid device id(%d)\n", __func__, id);
	break;
	}
}

#endif /* __ASM_PLAT_FB_CORE_H */
