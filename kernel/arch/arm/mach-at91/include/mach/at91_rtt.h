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
#ifndef AT91_RTT_H
#define AT91_RTT_H

#define AT91_RTT_MR		0x00			/* Real-time Mode Register */
#define		AT91_RTT_RTPRES		(0xffff << 0)		/* Real-time Timer Prescaler Value */
#define		AT91_RTT_ALMIEN		(1 << 16)		/* Alarm Interrupt Enable */
#define		AT91_RTT_RTTINCIEN	(1 << 17)		/* Real Time Timer Increment Interrupt Enable */
#define		AT91_RTT_RTTRST		(1 << 18)		/* Real Time Timer Restart */

#define AT91_RTT_AR		0x04			/* Real-time Alarm Register */
#define		AT91_RTT_ALMV		(0xffffffff)		/* Alarm Value */

#define AT91_RTT_VR		0x08			/* Real-time Value Register */
#define		AT91_RTT_CRTV		(0xffffffff)		/* Current Real-time Value */

#define AT91_RTT_SR		0x0c			/* Real-time Status Register */
#define		AT91_RTT_ALMS		(1 << 0)		/* Real-time Alarm Status */
#define		AT91_RTT_RTTINC		(1 << 1)		/* Real-time Timer Increment */

#endif
