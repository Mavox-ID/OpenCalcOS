/*
 * beep/include/beep/sunrpc/types.h
 *
 * Generic types and misc stuff for RPC.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#ifndef _BEEP_SUNRPC_TYPES_H_
#define _BEEP_SUNRPC_TYPES_H_

#include <beep/timer.h>
#include <beep/workqueue.h>
#include <beep/sunrpc/debug.h>
#include <beep/list.h>

/*
 * Shorthands
 */
#define signalled()		(signal_pending(current))

#endif /* _BEEP_SUNRPC_TYPES_H_ */
