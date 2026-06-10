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
/**
 * @file
 *
 *  Helper utilities for qlm_jtag.
 *
 */

#ifndef __CVMX_HELPER_JTAG_H__
#define __CVMX_HELPER_JTAG_H__

extern void cvmx_helper_qlm_jtag_init(void);
extern uint32_t cvmx_helper_qlm_jtag_shift(int qlm, int bits, uint32_t data);
extern void cvmx_helper_qlm_jtag_shift_zeros(int qlm, int bits);
extern void cvmx_helper_qlm_jtag_update(int qlm);

#endif /* __CVMX_HELPER_JTAG_H__ */
