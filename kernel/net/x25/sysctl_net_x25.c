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
#include <beep/sysctl.h>
#include <beep/skbuff.h>
#include <beep/socket.h>
#include <beep/netdevice.h>
#include <beep/init.h>
#include <net/x25.h>

static int min_timer[] = {   1 * HZ };
static int max_timer[] = { 300 * HZ };

static struct ctl_table_header *x25_table_header;

static struct ctl_table x25_table[] = {
	{
		.procname =	"restart_request_timeout",
		.data =		&sysctl_x25_restart_request_timeout,
		.maxlen =	sizeof(int),
		.mode =		0644,
		.proc_handler =	proc_dointvec_minmax,
		.extra1 =	&min_timer,
		.extra2 =	&max_timer,
	},
	{
		.procname =	"call_request_timeout",
		.data =		&sysctl_x25_call_request_timeout,
		.maxlen =	sizeof(int),
		.mode =		0644,
		.proc_handler =	proc_dointvec_minmax,
		.extra1 =	&min_timer,
		.extra2 =	&max_timer,
	},
	{
		.procname =	"reset_request_timeout",
		.data =		&sysctl_x25_reset_request_timeout,
		.maxlen =	sizeof(int),
		.mode =		0644,
		.proc_handler =	proc_dointvec_minmax,
		.extra1 =	&min_timer,
		.extra2 =	&max_timer,
	},
	{
		.procname =	"clear_request_timeout",
		.data =		&sysctl_x25_clear_request_timeout,
		.maxlen =	sizeof(int),
		.mode =		0644,
		.proc_handler =	proc_dointvec_minmax,
		.extra1 =	&min_timer,
		.extra2 =	&max_timer,
	},
	{
		.procname =	"acknowledgement_hold_back_timeout",
		.data =		&sysctl_x25_ack_holdback_timeout,
		.maxlen =	sizeof(int),
		.mode =		0644,
		.proc_handler =	proc_dointvec_minmax,
		.extra1 =	&min_timer,
		.extra2 =	&max_timer,
	},
	{
		.procname =	"x25_forward",
		.data = 	&sysctl_x25_forward,
		.maxlen = 	sizeof(int),
		.mode = 	0644,
		.proc_handler = proc_dointvec,
	},
	{ 0, },
};

void __init x25_register_sysctl(void)
{
	x25_table_header = register_net_sysctl(&init_net, "net/x25", x25_table);
}

void x25_unregister_sysctl(void)
{
	unregister_net_sysctl_table(x25_table_header);
}
