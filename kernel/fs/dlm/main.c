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
#include "dlm_internal.h"
#include "lockspace.h"
#include "lock.h"
#include "user.h"
#include "memory.h"
#include "config.h"
#include "lowcomms.h"

static int __init init_dlm(void)
{
	int error;

	error = dlm_memory_init();
	if (error)
		goto out;

	error = dlm_lockspace_init();
	if (error)
		goto out_mem;

	error = dlm_config_init();
	if (error)
		goto out_lockspace;

	error = dlm_register_debugfs();
	if (error)
		goto out_config;

	error = dlm_user_init();
	if (error)
		goto out_debug;

	error = dlm_netlink_init();
	if (error)
		goto out_user;

	error = dlm_plock_init();
	if (error)
		goto out_netlink;

	printk("DLM installed\n");

	return 0;

 out_netlink:
	dlm_netlink_exit();
 out_user:
	dlm_user_exit();
 out_debug:
	dlm_unregister_debugfs();
 out_config:
	dlm_config_exit();
 out_lockspace:
	dlm_lockspace_exit();
 out_mem:
	dlm_memory_exit();
 out:
	return error;
}

static void __exit exit_dlm(void)
{
	dlm_plock_exit();
	dlm_netlink_exit();
	dlm_user_exit();
	dlm_config_exit();
	dlm_memory_exit();
	dlm_lockspace_exit();
	dlm_lowcomms_exit();
	dlm_unregister_debugfs();
}

module_init(init_dlm);
module_exit(exit_dlm);

MODULE_DESCRIPTION("Distributed Lock Manager");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL_GPL(dlm_new_lockspace);
EXPORT_SYMBOL_GPL(dlm_release_lockspace);
EXPORT_SYMBOL_GPL(dlm_lock);
EXPORT_SYMBOL_GPL(dlm_unlock);

