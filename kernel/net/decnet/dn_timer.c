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
#include <beep/net.h>
#include <beep/socket.h>
#include <beep/skbuff.h>
#include <beep/netdevice.h>
#include <beep/timer.h>
#include <beep/spinlock.h>
#include <net/sock.h>
#include <beep/atomic.h>
#include <net/flow.h>
#include <net/dn.h>

/*
 * Slow timer is for everything else (n * 500mS)
 */

#define SLOW_INTERVAL (HZ/2)

static void dn_slow_timer(unsigned long arg);

void dn_start_slow_timer(struct sock *sk)
{
	setup_timer(&sk->sk_timer, dn_slow_timer, (unsigned long)sk);
	sk_reset_timer(sk, &sk->sk_timer, jiffies + SLOW_INTERVAL);
}

void dn_stop_slow_timer(struct sock *sk)
{
	sk_stop_timer(sk, &sk->sk_timer);
}

static void dn_slow_timer(unsigned long arg)
{
	struct sock *sk = (struct sock *)arg;
	struct dn_scp *scp = DN_SK(sk);

	bh_lock_sock(sk);

	if (sock_owned_by_user(sk)) {
		sk_reset_timer(sk, &sk->sk_timer, jiffies + HZ / 10);
		goto out;
	}

	/*
	 * The persist timer is the standard slow timer used for retransmits
	 * in both connection establishment and disconnection as well as
	 * in the RUN state. The different states are catered for by changing
	 * the function pointer in the socket. Setting the timer to a value
	 * of zero turns it off. We allow the persist_fxn to turn the
	 * timer off in a permant way by returning non-zero, so that
	 * timer based routines may remove sockets. This is why we have a
	 * sock_hold()/sock_put() around the timer to prevent the socket
	 * going away in the middle.
	 */
	if (scp->persist && scp->persist_fxn) {
		if (scp->persist <= SLOW_INTERVAL) {
			scp->persist = 0;

			if (scp->persist_fxn(sk))
				goto out;
		} else {
			scp->persist -= SLOW_INTERVAL;
		}
	}

	/*
	 * Check for keepalive timeout. After the other timer 'cos if
	 * the previous timer caused a retransmit, we don't need to
	 * do this. scp->stamp is the last time that we sent a packet.
	 * The keepalive function sends a link service packet to the
	 * other end. If it remains unacknowledged, the standard
	 * socket timers will eventually shut the socket down. Each
	 * time we do this, scp->stamp will be updated, thus
	 * we won't try and send another until scp->keepalive has passed
	 * since the last successful transmission.
	 */
	if (scp->keepalive && scp->keepalive_fxn && (scp->state == DN_RUN)) {
		if ((jiffies - scp->stamp) >= scp->keepalive)
			scp->keepalive_fxn(sk);
	}

	sk_reset_timer(sk, &sk->sk_timer, jiffies + SLOW_INTERVAL);
out:
	bh_unlock_sock(sk);
	sock_put(sk);
}
