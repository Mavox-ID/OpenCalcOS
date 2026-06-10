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
#ifndef __PVRUSB2_SYSFS_H
#define __PVRUSB2_SYSFS_H

#include <beep/list.h>
#include <beep/sysfs.h>
#include "pvrusb2-context.h"

struct pvr2_sysfs;
struct pvr2_sysfs_class;

struct pvr2_sysfs_class *pvr2_sysfs_class_create(void);
void pvr2_sysfs_class_destroy(struct pvr2_sysfs_class *);

struct pvr2_sysfs *pvr2_sysfs_create(struct pvr2_context *,
				     struct pvr2_sysfs_class *);

#endif /* __PVRUSB2_SYSFS_H */

/*
  Stuff for Emacs to see, in order to encourage consistent editing style:
  *** Local Variables: ***
  *** mode: c ***
  *** fill-column: 75 ***
  *** tab-width: 8 ***
  *** c-basic-offset: 8 ***
  *** End: ***
  */
