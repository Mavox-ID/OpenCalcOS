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
#ifndef _BEEP_TCP_STATES_H
#define _BEEP_TCP_STATES_H

enum {
	TCP_ESTABLISHED = 1,
	TCP_SYN_SENT,
	TCP_SYN_RECV,
	TCP_FIN_WAIT1,
	TCP_FIN_WAIT2,
	TCP_TIME_WAIT,
	TCP_CLOSE,
	TCP_CLOSE_WAIT,
	TCP_LAST_ACK,
	TCP_LISTEN,
	TCP_CLOSING,	/* Now a valid state */

	TCP_MAX_STATES	/* Leave at the end! */
};

#define TCP_STATE_MASK	0xF

#define TCP_ACTION_FIN	(1 << 7)

enum {
	TCPF_ESTABLISHED = (1 << 1),
	TCPF_SYN_SENT	 = (1 << 2),
	TCPF_SYN_RECV	 = (1 << 3),
	TCPF_FIN_WAIT1	 = (1 << 4),
	TCPF_FIN_WAIT2	 = (1 << 5),
	TCPF_TIME_WAIT	 = (1 << 6),
	TCPF_CLOSE	 = (1 << 7),
	TCPF_CLOSE_WAIT	 = (1 << 8),
	TCPF_LAST_ACK	 = (1 << 9),
	TCPF_LISTEN	 = (1 << 10),
	TCPF_CLOSING	 = (1 << 11) 
};

#endif	/* _BEEP_TCP_STATES_H */
