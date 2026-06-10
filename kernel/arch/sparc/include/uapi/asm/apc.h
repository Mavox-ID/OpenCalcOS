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
#ifndef _SPARC_APC_H
#define _SPARC_APC_H

#include <beep/ioctl.h>

#define APC_IOC	'A'

#define APCIOCGFANCTL _IOR(APC_IOC, 0x00, int)	/* Get fan speed	*/
#define APCIOCSFANCTL _IOW(APC_IOC, 0x01, int)	/* Set fan speed	*/

#define APCIOCGCPWR   _IOR(APC_IOC, 0x02, int)	/* Get CPOWER state	*/
#define APCIOCSCPWR   _IOW(APC_IOC, 0x03, int)	/* Set CPOWER state	*/

#define APCIOCGBPORT   _IOR(APC_IOC, 0x04, int)	/* Get BPORT state 	*/
#define APCIOCSBPORT   _IOW(APC_IOC, 0x05, int)	/* Set BPORT state	*/

/*
 * Register offsets
 */
#define APC_IDLE_REG	0x00
#define APC_FANCTL_REG	0x20
#define APC_CPOWER_REG	0x24
#define APC_BPORT_REG	0x30

#define APC_REGMASK		0x01
#define APC_BPMASK		0x03

/*
 * IDLE - CPU standby values (set to initiate standby)
 */
#define APC_IDLE_ON		0x01

/*
 * FANCTL - Fan speed control state values
 */
#define APC_FANCTL_HI	0x00	/* Fan speed high	*/
#define APC_FANCTL_LO	0x01	/* Fan speed low	*/

/*
 * CPWR - Convenience power outlet state values 
 */
#define APC_CPOWER_ON	0x00	/* Conv power on	*/
#define APC_CPOWER_OFF	0x01	/* Conv power off	*/

/*
 * BPA/BPB - Read-Write "Bit Ports" state values (reset to 0 at power-on)
 *
 * WARNING: Internal usage of bit ports is platform dependent--
 * don't modify BPORT settings unless you know what you are doing.
 * 
 * On SS5 BPA seems to toggle onboard ethernet loopback... -E
 */
#define APC_BPORT_A		0x01	/* Bit Port A		*/
#define APC_BPORT_B		0x02	/* Bit Port B		*/

#endif /* !(_SPARC_APC_H) */
