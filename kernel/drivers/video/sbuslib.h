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
#ifndef _SBUSLIB_H
#define _SBUSLIB_H

struct sbus_mmap_map {
	unsigned long voff;
	unsigned long poff;
	unsigned long size;
};

#define SBUS_MMAP_FBSIZE(n) (-n)
#define SBUS_MMAP_EMPTY	0x80000000

extern void sbusfb_fill_var(struct fb_var_screeninfo *var,
			    struct device_node *dp, int bpp);
struct vm_area_struct;
extern int sbusfb_mmap_helper(struct sbus_mmap_map *map,
			      unsigned long physbase, unsigned long fbsize,
			      unsigned long iospace,
			      struct vm_area_struct *vma);
int sbusfb_ioctl_helper(unsigned long cmd, unsigned long arg,
			struct fb_info *info,
			int type, int fb_depth, unsigned long fb_size);
int sbusfb_compat_ioctl(struct fb_info *info, unsigned int cmd,
			unsigned long arg);

#endif /* _SBUSLIB_H */
