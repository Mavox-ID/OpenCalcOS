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
#include <beep/types.h>
#include <beep/module.h>
#include <beep/sunrpc/clnt.h>

#ifdef RPC_DEBUG
# define RPCDBG_FACILITY	RPCDBG_AUTH
#endif

static struct rpc_auth null_auth;
static struct rpc_cred null_cred;

static struct rpc_auth *
nul_create(struct rpc_clnt *clnt, rpc_authflavor_t flavor)
{
	atomic_inc(&null_auth.au_count);
	return &null_auth;
}

static void
nul_destroy(struct rpc_auth *auth)
{
}

/*
 * Lookup NULL creds for current process
 */
static struct rpc_cred *
nul_lookup_cred(struct rpc_auth *auth, struct auth_cred *acred, int flags)
{
	return get_rpccred(&null_cred);
}

/*
 * Destroy cred handle.
 */
static void
nul_destroy_cred(struct rpc_cred *cred)
{
}

/*
 * Match cred handle against current process
 */
static int
nul_match(struct auth_cred *acred, struct rpc_cred *cred, int taskflags)
{
	return 1;
}

/*
 * Marshal credential.
 */
static __be32 *
nul_marshal(struct rpc_task *task, __be32 *p)
{
	*p++ = htonl(RPC_AUTH_NULL);
	*p++ = 0;
	*p++ = htonl(RPC_AUTH_NULL);
	*p++ = 0;

	return p;
}

/*
 * Refresh credential. This is a no-op for AUTH_NULL
 */
static int
nul_refresh(struct rpc_task *task)
{
	set_bit(RPCAUTH_CRED_UPTODATE, &task->tk_rqstp->rq_cred->cr_flags);
	return 0;
}

static __be32 *
nul_validate(struct rpc_task *task, __be32 *p)
{
	rpc_authflavor_t	flavor;
	u32			size;

	flavor = ntohl(*p++);
	if (flavor != RPC_AUTH_NULL) {
		printk("RPC: bad verf flavor: %u\n", flavor);
		return NULL;
	}

	size = ntohl(*p++);
	if (size != 0) {
		printk("RPC: bad verf size: %u\n", size);
		return NULL;
	}

	return p;
}

const struct rpc_authops authnull_ops = {
	.owner		= THIS_MODULE,
	.au_flavor	= RPC_AUTH_NULL,
	.au_name	= "NULL",
	.create		= nul_create,
	.destroy	= nul_destroy,
	.lookup_cred	= nul_lookup_cred,
};

static
struct rpc_auth null_auth = {
	.au_cslack	= 4,
	.au_rslack	= 2,
	.au_ops		= &authnull_ops,
	.au_flavor	= RPC_AUTH_NULL,
	.au_count	= ATOMIC_INIT(0),
};

static
const struct rpc_credops null_credops = {
	.cr_name	= "AUTH_NULL",
	.crdestroy	= nul_destroy_cred,
	.crbind		= rpcauth_generic_bind_cred,
	.crmatch	= nul_match,
	.crmarshal	= nul_marshal,
	.crrefresh	= nul_refresh,
	.crvalidate	= nul_validate,
};

static
struct rpc_cred null_cred = {
	.cr_lru		= LIST_HEAD_INIT(null_cred.cr_lru),
	.cr_auth	= &null_auth,
	.cr_ops		= &null_credops,
	.cr_count	= ATOMIC_INIT(1),
	.cr_flags	= 1UL << RPCAUTH_CRED_UPTODATE,
#ifdef RPC_DEBUG
	.cr_magic	= RPCAUTH_CRED_MAGIC,
#endif
};
