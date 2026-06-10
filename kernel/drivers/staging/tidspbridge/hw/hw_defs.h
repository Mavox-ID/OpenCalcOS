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
#ifndef _HW_DEFS_H
#define _HW_DEFS_H

/* Page size */
#define HW_PAGE_SIZE4KB   0x1000
#define HW_PAGE_SIZE64KB  0x10000
#define HW_PAGE_SIZE1MB   0x100000
#define HW_PAGE_SIZE16MB  0x1000000

/* hw_status:  return type for HW API */
typedef long hw_status;

/*  Macro used to set and clear any bit */
#define HW_CLEAR	0
#define HW_SET		1

/* hw_endianism_t:  Enumerated Type used to specify the endianism
 *		Do NOT change these values. They are used as bit fields. */
enum hw_endianism_t {
	HW_LITTLE_ENDIAN,
	HW_BIG_ENDIAN
};

/* hw_element_size_t:  Enumerated Type used to specify the element size
 *		Do NOT change these values. They are used as bit fields. */
enum hw_element_size_t {
	HW_ELEM_SIZE8BIT,
	HW_ELEM_SIZE16BIT,
	HW_ELEM_SIZE32BIT,
	HW_ELEM_SIZE64BIT
};

/* hw_idle_mode_t:  Enumerated Type used to specify Idle modes */
enum hw_idle_mode_t {
	HW_FORCE_IDLE,
	HW_NO_IDLE,
	HW_SMART_IDLE
};

#endif /* _HW_DEFS_H */
