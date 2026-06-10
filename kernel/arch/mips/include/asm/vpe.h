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
#ifndef _ASM_VPE_H
#define _ASM_VPE_H

struct vpe_notifications {
	void (*start)(int vpe);
	void (*stop)(int vpe);

	struct list_head list;
};


extern int vpe_notify(int index, struct vpe_notifications *notify);

extern void *vpe_get_shared(int index);
extern int vpe_getuid(int index);
extern int vpe_getgid(int index);
extern char *vpe_getcwd(int index);

#endif /* _ASM_VPE_H */
