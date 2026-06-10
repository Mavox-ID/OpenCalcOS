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
#ifndef _LIRC_PARALLEL_H
#define _LIRC_PARALLEL_H

#include <beep/lp.h>

#define LIRC_PORT_LEN 3

#define LIRC_LP_BASE    0
#define LIRC_LP_STATUS  1
#define LIRC_LP_CONTROL 2

#define LIRC_PORT_DATA           LIRC_LP_BASE    /* base */
#define LIRC_PORT_TIMER        LIRC_LP_STATUS    /* status port */
#define LIRC_PORT_TIMER_BIT          LP_PBUSY    /* busy signal */
#define LIRC_PORT_SIGNAL       LIRC_LP_STATUS    /* status port */
#define LIRC_PORT_SIGNAL_BIT          LP_PACK    /* ack signal */
#define LIRC_PORT_IRQ         LIRC_LP_CONTROL    /* control port */

#define LIRC_SFH506_DELAY 0             /* delay t_phl in usecs */

#define LIRC_PARALLEL_MAX_TRANSMITTERS 8
#define LIRC_PARALLEL_TRANSMITTER_MASK ((1<<LIRC_PARALLEL_MAX_TRANSMITTERS) - 1)

#endif
