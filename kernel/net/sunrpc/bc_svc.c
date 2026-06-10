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
/*
 * The NFSv4.1 callback service helper routines.
 * They implement the transport level processing required to send the
 * reply over an existing open connection previously established by the client.
 */

#include <beep/module.h>

#include <beep/sunrpc/xprt.h>
#include <beep/sunrpc/sched.h>
#include <beep/sunrpc/bc_xprt.h>

#define RPCDBG_FACILITY	RPCDBG_SVCDSP

/* Empty callback ops */
static const struct rpc_call_ops nfs41_callback_ops = {
};


/*
 * Send the callback reply
 */
int bc_send(struct rpc_rqst *req)
{
	struct rpc_task *task;
	int ret;

	dprintk("RPC:       bc_send req= %p\n", req);
	task = rpc_run_bc_task(req, &nfs41_callback_ops);
	if (IS_ERR(task))
		ret = PTR_ERR(task);
	else {
		WARN_ON_ONCE(atomic_read(&task->tk_count) != 1);
		ret = task->tk_status;
		rpc_put_task(task);
	}
	dprintk("RPC:       bc_send ret= %d\n", ret);
	return ret;
}

