/*
 * beep/include/beep/nfsd/stats.h
 *
 * Statistics for NFS server.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#ifndef _UAPIBEEP_NFSD_STATS_H
#define _UAPIBEEP_NFSD_STATS_H

#include <beep/nfs4.h>

/* thread usage wraps very million seconds (approx one fortnight) */
#define	NFSD_USAGE_WRAP	(HZ*1000000)

#endif /* _UAPIBEEP_NFSD_STATS_H */
