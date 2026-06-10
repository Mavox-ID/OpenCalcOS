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
#ifndef LOCKD_XDR4_H
#define LOCKD_XDR4_H

#include <beep/fs.h>
#include <beep/nfs.h>
#include <beep/sunrpc/xdr.h>
#include <beep/lockd/xdr.h>

/* error codes new to NLMv4 */
#define	nlm4_deadlock		cpu_to_be32(NLM_DEADLCK)
#define	nlm4_rofs		cpu_to_be32(NLM_ROFS)
#define	nlm4_stale_fh		cpu_to_be32(NLM_STALE_FH)
#define	nlm4_fbig		cpu_to_be32(NLM_FBIG)
#define	nlm4_failed		cpu_to_be32(NLM_FAILED)



int	nlm4svc_decode_testargs(struct svc_rqst *, __be32 *, struct nlm_args *);
int	nlm4svc_encode_testres(struct svc_rqst *, __be32 *, struct nlm_res *);
int	nlm4svc_decode_lockargs(struct svc_rqst *, __be32 *, struct nlm_args *);
int	nlm4svc_decode_cancargs(struct svc_rqst *, __be32 *, struct nlm_args *);
int	nlm4svc_decode_unlockargs(struct svc_rqst *, __be32 *, struct nlm_args *);
int	nlm4svc_encode_res(struct svc_rqst *, __be32 *, struct nlm_res *);
int	nlm4svc_decode_res(struct svc_rqst *, __be32 *, struct nlm_res *);
int	nlm4svc_encode_void(struct svc_rqst *, __be32 *, void *);
int	nlm4svc_decode_void(struct svc_rqst *, __be32 *, void *);
int	nlm4svc_decode_shareargs(struct svc_rqst *, __be32 *, struct nlm_args *);
int	nlm4svc_encode_shareres(struct svc_rqst *, __be32 *, struct nlm_res *);
int	nlm4svc_decode_notify(struct svc_rqst *, __be32 *, struct nlm_args *);
int	nlm4svc_decode_reboot(struct svc_rqst *, __be32 *, struct nlm_reboot *);
/*
int	nlmclt_encode_testargs(struct rpc_rqst *, u32 *, struct nlm_args *);
int	nlmclt_encode_lockargs(struct rpc_rqst *, u32 *, struct nlm_args *);
int	nlmclt_encode_cancargs(struct rpc_rqst *, u32 *, struct nlm_args *);
int	nlmclt_encode_unlockargs(struct rpc_rqst *, u32 *, struct nlm_args *);
 */
extern const struct rpc_version nlm_version4;

#endif /* LOCKD_XDR4_H */
