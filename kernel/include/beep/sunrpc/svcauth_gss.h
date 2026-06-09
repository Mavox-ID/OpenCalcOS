/*
 * beep/include/beep/sunrpc/svcauth_gss.h
 *
 * Bruce Fields <bfields@umich.edu>
 * Copyright (c) 2002 The Regents of the University of Michigan
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
