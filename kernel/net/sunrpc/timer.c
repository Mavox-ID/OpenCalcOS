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
#include <asm/param.h>

#include <beep/types.h>
#include <beep/unistd.h>
#include <beep/module.h>

#include <beep/sunrpc/clnt.h>

#define RPC_RTO_MAX (60*HZ)
#define RPC_RTO_INIT (HZ/5)
#define RPC_RTO_MIN (HZ/10)

/**
 * rpc_init_rtt - Initialize an RPC RTT estimator context
 * @rt: context to initialize
 * @timeo: initial timeout value, in jiffies
 *
 */
void rpc_init_rtt(struct rpc_rtt *rt, unsigned long timeo)
{
	unsigned long init = 0;
	unsigned int i;

	rt->timeo = timeo;

	if (timeo > RPC_RTO_INIT)
		init = (timeo - RPC_RTO_INIT) << 3;
	for (i = 0; i < 5; i++) {
		rt->srtt[i] = init;
		rt->sdrtt[i] = RPC_RTO_INIT;
		rt->ntimeouts[i] = 0;
	}
}
EXPORT_SYMBOL_GPL(rpc_init_rtt);

/**
 * rpc_update_rtt - Update an RPC RTT estimator context
 * @rt: context to update
 * @timer: timer array index (request type)
 * @m: recent actual RTT, in jiffies
 *
 * NB: When computing the smoothed RTT and standard deviation,
 *     be careful not to produce negative intermediate results.
 */
void rpc_update_rtt(struct rpc_rtt *rt, unsigned int timer, long m)
{
	long *srtt, *sdrtt;

	if (timer-- == 0)
		return;

	/* jiffies wrapped; ignore this one */
	if (m < 0)
		return;

	if (m == 0)
		m = 1L;

	srtt = (long *)&rt->srtt[timer];
	m -= *srtt >> 3;
	*srtt += m;

	if (m < 0)
		m = -m;

	sdrtt = (long *)&rt->sdrtt[timer];
	m -= *sdrtt >> 2;
	*sdrtt += m;

	/* Set lower bound on the variance */
	if (*sdrtt < RPC_RTO_MIN)
		*sdrtt = RPC_RTO_MIN;
}
EXPORT_SYMBOL_GPL(rpc_update_rtt);

/**
 * rpc_calc_rto - Provide an estimated timeout value
 * @rt: context to use for calculation
 * @timer: timer array index (request type)
 *
 * Estimate RTO for an NFS RPC sent via an unreliable datagram.  Use
 * the mean and mean deviation of RTT for the appropriate type of RPC
 * for frequently issued RPCs, and a fixed default for the others.
 *
 * The justification for doing "other" this way is that these RPCs
 * happen so infrequently that timer estimation would probably be
 * stale.  Also, since many of these RPCs are non-idempotent, a
 * conservative timeout is desired.
 *
 * getattr, lookup,
 * read, write, commit     - A+4D
 * other                   - timeo
 */
unsigned long rpc_calc_rto(struct rpc_rtt *rt, unsigned int timer)
{
	unsigned long res;

	if (timer-- == 0)
		return rt->timeo;

	res = ((rt->srtt[timer] + 7) >> 3) + rt->sdrtt[timer];
	if (res > RPC_RTO_MAX)
		res = RPC_RTO_MAX;

	return res;
}
EXPORT_SYMBOL_GPL(rpc_calc_rto);
