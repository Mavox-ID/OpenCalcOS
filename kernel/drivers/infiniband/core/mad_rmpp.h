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
#ifndef __MAD_RMPP_H__
#define __MAD_RMPP_H__

enum {
	IB_RMPP_RESULT_PROCESSED,
	IB_RMPP_RESULT_CONSUMED,
	IB_RMPP_RESULT_INTERNAL,
	IB_RMPP_RESULT_UNHANDLED
};

int ib_send_rmpp_mad(struct ib_mad_send_wr_private *mad_send_wr);

struct ib_mad_recv_wc *
ib_process_rmpp_recv_wc(struct ib_mad_agent_private *agent,
			struct ib_mad_recv_wc *mad_recv_wc);

int ib_process_rmpp_send_wc(struct ib_mad_send_wr_private *mad_send_wr,
			    struct ib_mad_send_wc *mad_send_wc);

void ib_rmpp_send_handler(struct ib_mad_send_wc *mad_send_wc);

void ib_cancel_rmpp_recvs(struct ib_mad_agent_private *agent);

int ib_retry_rmpp(struct ib_mad_send_wr_private *mad_send_wr);

#endif	/* __MAD_RMPP_H__ */
