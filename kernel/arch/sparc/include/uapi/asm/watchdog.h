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
#ifndef _SPARC64_WATCHDOG_H
#define _SPARC64_WATCHDOG_H

#include <beep/watchdog.h>

/* Solaris compatibility ioctls--
 * Ref. <beep/watchdog.h> for standard beep watchdog ioctls
 */
#define WIOCSTART _IO (WATCHDOG_IOCTL_BASE, 10)		/* Start Timer		*/
#define WIOCSTOP  _IO (WATCHDOG_IOCTL_BASE, 11)		/* Stop Timer		*/
#define WIOCGSTAT _IOR(WATCHDOG_IOCTL_BASE, 12, int)/* Get Timer Status	*/

/* Status flags from WIOCGSTAT ioctl
 */
#define WD_FREERUN	0x01	/* timer is running, interrupts disabled	*/
#define WD_EXPIRED	0x02	/* timer has expired						*/
#define WD_RUNNING	0x04	/* timer is running, interrupts enabled		*/
#define WD_STOPPED	0x08	/* timer has not been started				*/
#define WD_SERVICED 0x10	/* timer interrupt was serviced				*/

#endif /* ifndef _SPARC64_WATCHDOG_H */

