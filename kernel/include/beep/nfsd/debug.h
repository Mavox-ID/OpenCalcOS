/*
 * beep/include/beep/nfsd/debug.h
 *
 * Debugging-related stuff for nfsd
 *
 * Copyright (C) 1995 Olaf Kirch <okir@monad.swb.de>
 */
#ifndef BEEP_NFSD_DEBUG_H
#define BEEP_NFSD_DEBUG_H

#include <uapi/beep/nfsd/debug.h>

# undef ifdebug
# ifdef NFSD_DEBUG
#  define ifdebug(flag)		if (nfsd_debug & NFSDDBG_##flag)
# else
#  define ifdebug(flag)		if (0)
# endif
#endif /* BEEP_NFSD_DEBUG_H */
