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
#if !defined(WM_IOCTL_H_20080714)
#define WM_IOCTL_H_20080714
#if !defined(__KERNEL__)
#include <net/if.h>
#endif

#define NETLINK_WIMAX	31

#define SIOCWMIOCTL			SIOCDEVPRIVATE

#define SIOCG_DATA			0x8D10
#define SIOCS_DATA			0x8D11

enum {
	SIOC_DATA_FSM,
	SIOC_DATA_NETLIST,
	SIOC_DATA_CONNNSP,
	SIOC_DATA_CONNCOMP,
	SIOC_DATA_PROFILEID,

	SIOC_DATA_END
};

#define SIOC_DATA_MAX			16

/* FSM */
enum {
	M_INIT = 0,
	M_OPEN_OFF,
	M_OPEN_ON,
	M_SCAN,
	M_CONNECTING,
	M_CONNECTED,
	M_FSM_END,

	C_INIT = 0,
	C_CONNSTART,
	C_ASSOCSTART,
	C_RNG,
	C_SBC,
	C_AUTH,
	C_REG,
	C_DSX,
	C_ASSOCCOMPLETE,
	C_CONNCOMPLETE,
	C_FSM_END,

	D_INIT = 0,
	D_READY,
	D_LISTEN,
	D_IPACQUISITION,

	END_FSM
};

struct fsm_s {
	int		m_status;	/*main status*/
	int		c_status;	/*connection status*/
	int		d_status;	/*oma-dm status*/
};

struct data_s {
	int		size;
	void	*buf;
};

struct wm_req_s {
	union {
		char	ifrn_name[IFNAMSIZ];
	} ifr_ifrn;

	unsigned short	cmd;

	unsigned short	data_id;
	struct data_s	data;

/* NOTE: sizeof(struct wm_req_s) must be less than sizeof(struct ifreq). */
};

#ifndef ifr_name
#define ifr_name	ifr_ifrn.ifrn_name
#endif

#endif
