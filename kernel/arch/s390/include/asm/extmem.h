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
#ifndef _ASM_S390X_DCSS_H
#define _ASM_S390X_DCSS_H
#ifndef __ASSEMBLY__

/* possible values for segment type as returned by segment_info */
#define SEG_TYPE_SW 0
#define SEG_TYPE_EW 1
#define SEG_TYPE_SR 2
#define SEG_TYPE_ER 3
#define SEG_TYPE_SN 4
#define SEG_TYPE_EN 5
#define SEG_TYPE_SC 6
#define SEG_TYPE_EWEN 7

#define SEGMENT_SHARED 0
#define SEGMENT_EXCLUSIVE 1

int segment_load (char *name, int segtype, unsigned long *addr, unsigned long *length);
void segment_unload(char *name);
void segment_save(char *name);
int segment_type (char* name);
int segment_modify_shared (char *name, int do_nonshared);
void segment_warning(int rc, char *seg_name);

#endif
#endif
