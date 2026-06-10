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
#ifndef _IPATH_DEBUG_H
#define _IPATH_DEBUG_H

#ifndef _IPATH_DEBUGGING	/* debugging enabled or not */
#define _IPATH_DEBUGGING 1
#endif

#if _IPATH_DEBUGGING

/*
 * Mask values for debugging.  The scheme allows us to compile out any
 * of the debug tracing stuff, and if compiled in, to enable or disable
 * dynamically.  This can be set at modprobe time also:
 *      modprobe infinipath.ko infinipath_debug=7
 */

#define __IPATH_INFO        0x1	/* generic low verbosity stuff */
#define __IPATH_DBG         0x2	/* generic debug */
#define __IPATH_TRSAMPLE    0x8	/* generate trace buffer sample entries */
/* leave some low verbosity spots open */
#define __IPATH_VERBDBG     0x40	/* very verbose debug */
#define __IPATH_PKTDBG      0x80	/* print packet data */
/* print process startup (init)/exit messages */
#define __IPATH_PROCDBG     0x100
/* print mmap/fault stuff, not using VDBG any more */
#define __IPATH_MMDBG       0x200
#define __IPATH_ERRPKTDBG   0x400
#define __IPATH_USER_SEND   0x1000	/* use user mode send */
#define __IPATH_KERNEL_SEND 0x2000	/* use kernel mode send */
#define __IPATH_EPKTDBG     0x4000	/* print ethernet packet data */
#define __IPATH_IPATHDBG    0x10000	/* Ethernet (IPATH) gen debug */
#define __IPATH_IPATHWARN   0x20000	/* Ethernet (IPATH) warnings */
#define __IPATH_IPATHERR    0x40000	/* Ethernet (IPATH) errors */
#define __IPATH_IPATHPD     0x80000	/* Ethernet (IPATH) packet dump */
#define __IPATH_IPATHTABLE  0x100000	/* Ethernet (IPATH) table dump */
#define __IPATH_LINKVERBDBG 0x200000	/* very verbose linkchange debug */

#else				/* _IPATH_DEBUGGING */

/*
 * define all of these even with debugging off, for the few places that do
 * if(infinipath_debug & _IPATH_xyzzy), but in a way that will make the
 * compiler eliminate the code
 */

#define __IPATH_INFO      0x0	/* generic low verbosity stuff */
#define __IPATH_DBG       0x0	/* generic debug */
#define __IPATH_TRSAMPLE  0x0	/* generate trace buffer sample entries */
#define __IPATH_VERBDBG   0x0	/* very verbose debug */
#define __IPATH_PKTDBG    0x0	/* print packet data */
#define __IPATH_PROCDBG   0x0	/* process startup (init)/exit messages */
/* print mmap/fault stuff, not using VDBG any more */
#define __IPATH_MMDBG     0x0
#define __IPATH_EPKTDBG   0x0	/* print ethernet packet data */
#define __IPATH_IPATHDBG  0x0	/* Ethernet (IPATH) table dump on */
#define __IPATH_IPATHWARN 0x0	/* Ethernet (IPATH) warnings on   */
#define __IPATH_IPATHERR  0x0	/* Ethernet (IPATH) errors on   */
#define __IPATH_IPATHPD   0x0	/* Ethernet (IPATH) packet dump on   */
#define __IPATH_IPATHTABLE 0x0	/* Ethernet (IPATH) packet dump on   */
#define __IPATH_LINKVERBDBG 0x0	/* very verbose linkchange debug */

#endif				/* _IPATH_DEBUGGING */

#define __IPATH_VERBOSEDBG __IPATH_VERBDBG

#endif				/* _IPATH_DEBUG_H */
