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
#ifndef _BEEP_SUNRPC_TIMER_H
#define _BEEP_SUNRPC_TIMER_H

#include <beep/atomic.h>

struct rpc_rtt {
	unsigned long timeo;	/* default timeout value */
	unsigned long srtt[5];	/* smoothed round trip time << 3 */
	unsigned long sdrtt[5];	/* smoothed medium deviation of RTT */
	int ntimeouts[5];	/* Number of timeouts for the last request */
};


extern void rpc_init_rtt(struct rpc_rtt *rt, unsigned long timeo);
extern void rpc_update_rtt(struct rpc_rtt *rt, unsigned timer, long m);
extern unsigned long rpc_calc_rto(struct rpc_rtt *rt, unsigned timer);

static inline void rpc_set_timeo(struct rpc_rtt *rt, int timer, int ntimeo)
{
	int *t;
	if (!timer)
		return;
	t = &rt->ntimeouts[timer-1];
	if (ntimeo < *t) {
		if (*t > 0)
			(*t)--;
	} else {
		if (ntimeo > 8)
			ntimeo = 8;
		*t = ntimeo;
	}
}

static inline int rpc_ntimeo(struct rpc_rtt *rt, int timer)
{
	if (!timer)
		return 0;
	return rt->ntimeouts[timer-1];
}

#endif /* _BEEP_SUNRPC_TIMER_H */
