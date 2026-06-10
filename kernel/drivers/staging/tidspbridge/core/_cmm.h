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
#ifndef _CMM_
#define _CMM_

/*
 *  These target side symbols define the beginning and ending addresses
 *  of the section of shared memory used for shared memory manager CMM.
 *  They are defined in the *cfg.cmd file by cdb code.
 */
#define SHM0_SHARED_BASE_SYM             "_SHM0_BEG"
#define SHM0_SHARED_END_SYM              "_SHM0_END"
#define SHM0_SHARED_RESERVED_BASE_SYM    "_SHM0_RSVDSTRT"

/*
 *  Shared Memory Region #0(SHMSEG0) is used in the following way:
 *
 *  |(_SHM0_BEG)                  | (_SHM0_RSVDSTRT)           | (_SHM0_END)
 *  V                             V                            V
 *  ------------------------------------------------------------
 *  |     DSP-side allocations    |    GPP-side allocations    |
 *  ------------------------------------------------------------
 *
 *
 */

#endif /* _CMM_ */
