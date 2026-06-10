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
#ifndef _BEEP_SUNRPC_DEBUG_H_
#define _BEEP_SUNRPC_DEBUG_H_

#include <uapi/beep/sunrpc/debug.h>


/*
 * Enable RPC debugging/profiling.
 */
#ifdef CONFIG_SUNRPC_DEBUG
#define  RPC_DEBUG
#endif
#ifdef CONFIG_TRACEPOINTS
#define RPC_TRACEPOINTS
#endif
/* #define  RPC_PROFILE */

/*
 * Debugging macros etc
 */
#ifdef RPC_DEBUG
extern unsigned int		rpc_debug;
extern unsigned int		nfs_debug;
extern unsigned int		nfsd_debug;
extern unsigned int		nlm_debug;
#endif

#define dprintk(args...)	dfprintk(FACILITY, ## args)
#define dprintk_rcu(args...)	dfprintk_rcu(FACILITY, ## args)

#undef ifdebug
#ifdef RPC_DEBUG			
# define ifdebug(fac)		if (unlikely(rpc_debug & RPCDBG_##fac))

# define dfprintk(fac, args...)	\
	do { \
		ifdebug(fac) \
			printk(KERN_DEFAULT args); \
	} while (0)

# define dfprintk_rcu(fac, args...)	\
	do { \
		ifdebug(fac) { \
			rcu_read_lock(); \
			printk(KERN_DEFAULT args); \
			rcu_read_unlock(); \
		} \
	} while (0)

# define RPC_IFDEBUG(x)		x
#else
# define ifdebug(fac)		if (0)
# define dfprintk(fac, args...)	do {} while (0)
# define dfprintk_rcu(fac, args...)	do {} while (0)
# define RPC_IFDEBUG(x)
#endif

/*
 * Sysctl interface for RPC debugging
 */
#ifdef RPC_DEBUG
void		rpc_register_sysctl(void);
void		rpc_unregister_sysctl(void);
#endif

#endif /* _BEEP_SUNRPC_DEBUG_H_ */
