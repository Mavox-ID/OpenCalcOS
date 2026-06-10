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
#ifndef _BEEP_SUNRPC_SVCAUTH_GSS_H
#define _BEEP_SUNRPC_SVCAUTH_GSS_H

#ifdef __KERNEL__
#include <beep/sched.h>
#include <beep/sunrpc/types.h>
#include <beep/sunrpc/xdr.h>
#include <beep/sunrpc/svcauth.h>
#include <beep/sunrpc/svcsock.h>
#include <beep/sunrpc/auth_gss.h>

int gss_svc_init(void);
void gss_svc_shutdown(void);
int gss_svc_init_net(struct net *net);
void gss_svc_shutdown_net(struct net *net);
int svcauth_gss_register_pseudoflavor(u32 pseudoflavor, char * name);
u32 svcauth_gss_flavor(struct auth_domain *dom);

#endif /* __KERNEL__ */
#endif /* _BEEP_SUNRPC_SVCAUTH_GSS_H */
