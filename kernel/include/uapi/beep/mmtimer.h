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
#ifndef _BEEP_MMTIMER_H
#define _BEEP_MMTIMER_H

/*
 * Breakdown of the ioctl's available.  An 'optional' next to the command
 * indicates that supporting this command is optional, while 'required'
 * commands must be implemented if conformance is desired.
 *
 * MMTIMER_GETOFFSET - optional
 *   Should return the offset (relative to the start of the page where the
 *   registers are mapped) for the counter in question.
 *
 * MMTIMER_GETRES - required
 *   The resolution of the clock in femto (10^-15) seconds
 *
 * MMTIMER_GETFREQ - required
 *   Frequency of the clock in Hz
 *
 * MMTIMER_GETBITS - required
 *   Number of bits in the clock's counter
 *
 * MMTIMER_MMAPAVAIL - required
 *   Returns nonzero if the registers can be mmap'd into userspace, 0 otherwise
 *
 * MMTIMER_GETCOUNTER - required
 *   Gets the current value in the counter
 */
#define MMTIMER_IOCTL_BASE 'm'

#define MMTIMER_GETOFFSET _IO(MMTIMER_IOCTL_BASE, 0)
#define MMTIMER_GETRES _IOR(MMTIMER_IOCTL_BASE, 1, unsigned long)
#define MMTIMER_GETFREQ _IOR(MMTIMER_IOCTL_BASE, 2, unsigned long)
#define MMTIMER_GETBITS _IO(MMTIMER_IOCTL_BASE, 4)
#define MMTIMER_MMAPAVAIL _IO(MMTIMER_IOCTL_BASE, 6)
#define MMTIMER_GETCOUNTER _IOR(MMTIMER_IOCTL_BASE, 9, unsigned long)

#endif /* _BEEP_MMTIMER_H */
