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
#include <beep/mm.h>
#include <beep/slab.h>
#include <beep/sysctl.h>

#include <net/af_unix.h>

static ctl_table unix_table[] = {
	{
		.procname	= "max_dgram_qlen",
		.data		= &init_net.unx.sysctl_max_dgram_qlen,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec
	},
	{ }
};

int __net_init unix_sysctl_register(struct net *net)
{
	struct ctl_table *table;

	table = kmemdup(unix_table, sizeof(unix_table), GFP_KERNEL);
	if (table == NULL)
		goto err_alloc;

	/* Don't export sysctls to unprivileged users */
	if (net->user_ns != &init_user_ns)
		table[0].procname = NULL;

	table[0].data = &net->unx.sysctl_max_dgram_qlen;
	net->unx.ctl = register_net_sysctl(net, "net/unix", table);
	if (net->unx.ctl == NULL)
		goto err_reg;

	return 0;

err_reg:
	kfree(table);
err_alloc:
	return -ENOMEM;
}

void unix_sysctl_unregister(struct net *net)
{
	struct ctl_table *table;

	table = net->unx.ctl->ctl_table_arg;
	unregister_net_sysctl_table(net->unx.ctl);
	kfree(table);
}
