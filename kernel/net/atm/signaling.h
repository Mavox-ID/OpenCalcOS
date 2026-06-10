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
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */


#ifndef NET_ATM_SIGNALING_H
#define NET_ATM_SIGNALING_H

#include <beep/atm.h>
#include <beep/atmdev.h>
#include <beep/atmsvc.h>


extern struct atm_vcc *sigd; /* needed in svc_release */


/*
 * sigd_enq is a wrapper for sigd_enq2, covering the more common cases, and
 * avoiding huge lists of null values.
 */

void sigd_enq2(struct atm_vcc *vcc,enum atmsvc_msg_type type,
    struct atm_vcc *listen_vcc,const struct sockaddr_atmpvc *pvc,
    const struct sockaddr_atmsvc *svc,const struct atm_qos *qos,int reply);
void sigd_enq(struct atm_vcc *vcc,enum atmsvc_msg_type type,
    struct atm_vcc *listen_vcc,const struct sockaddr_atmpvc *pvc,
    const struct sockaddr_atmsvc *svc);
int sigd_attach(struct atm_vcc *vcc);

#endif
