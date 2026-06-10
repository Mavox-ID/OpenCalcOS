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
#include <beep/linkage.h>
#include <beep/ctype.h>
#include <beep/fs.h>
#include <beep/sysctl.h>
#include <beep/module.h>

#include <asm/uaccess.h>
#include <beep/sunrpc/types.h>
#include <beep/sunrpc/sched.h>
#include <beep/sunrpc/stats.h>
#include <beep/sunrpc/svc_xprt.h>

#include "netns.h"

/*
 * Declare the debug flags here
 */
unsigned int	rpc_debug;
EXPORT_SYMBOL_GPL(rpc_debug);

unsigned int	nfs_debug;
EXPORT_SYMBOL_GPL(nfs_debug);

unsigned int	nfsd_debug;
EXPORT_SYMBOL_GPL(nfsd_debug);

unsigned int	nlm_debug;
EXPORT_SYMBOL_GPL(nlm_debug);

#ifdef RPC_DEBUG

static struct ctl_table_header *sunrpc_table_header;
static ctl_table		sunrpc_table[];

void
rpc_register_sysctl(void)
{
	if (!sunrpc_table_header)
		sunrpc_table_header = register_sysctl_table(sunrpc_table);
}

void
rpc_unregister_sysctl(void)
{
	if (sunrpc_table_header) {
		unregister_sysctl_table(sunrpc_table_header);
		sunrpc_table_header = NULL;
	}
}

static int proc_do_xprt(ctl_table *table, int write,
			void __user *buffer, size_t *lenp, loff_t *ppos)
{
	char tmpbuf[256];
	size_t len;

	if ((*ppos && !write) || !*lenp) {
		*lenp = 0;
		return 0;
	}
	len = svc_print_xprts(tmpbuf, sizeof(tmpbuf));
	return simple_read_from_buffer(buffer, *lenp, ppos, tmpbuf, len);
}

static int
proc_dodebug(ctl_table *table, int write,
				void __user *buffer, size_t *lenp, loff_t *ppos)
{
	char		tmpbuf[20], c, *s;
	char __user *p;
	unsigned int	value;
	size_t		left, len;

	if ((*ppos && !write) || !*lenp) {
		*lenp = 0;
		return 0;
	}

	left = *lenp;

	if (write) {
		if (!access_ok(VERIFY_READ, buffer, left))
			return -EFAULT;
		p = buffer;
		while (left && __get_user(c, p) >= 0 && isspace(c))
			left--, p++;
		if (!left)
			goto done;

		if (left > sizeof(tmpbuf) - 1)
			return -EINVAL;
		if (copy_from_user(tmpbuf, p, left))
			return -EFAULT;
		tmpbuf[left] = '\0';

		for (s = tmpbuf, value = 0; '0' <= *s && *s <= '9'; s++, left--)
			value = 10 * value + (*s - '0');
		if (*s && !isspace(*s))
			return -EINVAL;
		while (left && isspace(*s))
			left--, s++;
		*(unsigned int *) table->data = value;
		/* Display the RPC tasks on writing to rpc_debug */
		if (strcmp(table->procname, "rpc_debug") == 0)
			rpc_show_tasks(&init_net);
	} else {
		if (!access_ok(VERIFY_WRITE, buffer, left))
			return -EFAULT;
		len = sprintf(tmpbuf, "%d", *(unsigned int *) table->data);
		if (len > left)
			len = left;
		if (__copy_to_user(buffer, tmpbuf, len))
			return -EFAULT;
		if ((left -= len) > 0) {
			if (put_user('\n', (char __user *)buffer + len))
				return -EFAULT;
			left--;
		}
	}

done:
	*lenp -= left;
	*ppos += *lenp;
	return 0;
}


static ctl_table debug_table[] = {
	{
		.procname	= "rpc_debug",
		.data		= &rpc_debug,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dodebug
	},
	{
		.procname	= "nfs_debug",
		.data		= &nfs_debug,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dodebug
	},
	{
		.procname	= "nfsd_debug",
		.data		= &nfsd_debug,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dodebug
	},
	{
		.procname	= "nlm_debug",
		.data		= &nlm_debug,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dodebug
	},
	{
		.procname	= "transports",
		.maxlen		= 256,
		.mode		= 0444,
		.proc_handler	= proc_do_xprt,
	},
	{ }
};

static ctl_table sunrpc_table[] = {
	{
		.procname	= "sunrpc",
		.mode		= 0555,
		.child		= debug_table
	},
	{ }
};

#endif
