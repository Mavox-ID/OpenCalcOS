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
#ifndef __FAULTINFO_I386_H
#define __FAULTINFO_I386_H

/* this structure contains the full arch-specific faultinfo
 * from the traps.
 * On i386, ptrace_faultinfo unfortunately doesn't provide
 * all the info, since trap_no is missing.
 * All common elements are defined at the same position in
 * both structures, thus making it easy to copy the
 * contents without knowledge about the structure elements.
 */
struct faultinfo {
        int error_code; /* in ptrace_faultinfo misleadingly called is_write */
        unsigned long cr2; /* in ptrace_faultinfo called addr */
        int trap_no; /* missing in ptrace_faultinfo */
};

#define FAULT_WRITE(fi) ((fi).error_code & 2)
#define FAULT_ADDRESS(fi) ((fi).cr2)

/* This is Page Fault */
#define SEGV_IS_FIXABLE(fi)	((fi)->trap_no == 14)

/* SKAS3 has no trap_no on i386, but get_skas_faultinfo() sets it to 0. */
#define SEGV_MAYBE_FIXABLE(fi)	((fi)->trap_no == 0 && ptrace_faultinfo)

#define PTRACE_FULL_FAULTINFO 0

#endif
