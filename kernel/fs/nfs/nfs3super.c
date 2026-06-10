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
#include <beep/module.h>
#include <beep/nfs_fs.h>
#include "internal.h"
#include "nfs.h"

static struct nfs_subversion nfs_v3 = {
	.owner = THIS_MODULE,
	.nfs_fs   = &nfs_fs_type,
	.rpc_vers = &nfs_version3,
	.rpc_ops  = &nfs_v3_clientops,
	.sops     = &nfs_sops,
};

static int __init init_nfs_v3(void)
{
	register_nfs_version(&nfs_v3);
	return 0;
}

static void __exit exit_nfs_v3(void)
{
	unregister_nfs_version(&nfs_v3);
}

MODULE_LICENSE("GPL");

module_init(init_nfs_v3);
module_exit(exit_nfs_v3);
