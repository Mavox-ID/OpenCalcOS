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
#ifndef __AGENT_H_
#define __AGENT_H_

#include <beep/err.h>
#include <rdma/ib_mad.h>

extern int ib_agent_port_open(struct ib_device *device, int port_num);

extern int ib_agent_port_close(struct ib_device *device, int port_num);

extern void agent_send_response(struct ib_mad *mad, struct ib_grh *grh,
				struct ib_wc *wc, struct ib_device *device,
				int port_num, int qpn);

#endif	/* __AGENT_H_ */
