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
#include <beep/edac.h>
#include <beep/atomic.h>
#include <beep/device.h>
#include <asm/edac.h>

int edac_op_state = EDAC_OPSTATE_INVAL;
EXPORT_SYMBOL_GPL(edac_op_state);

atomic_t edac_handlers = ATOMIC_INIT(0);
EXPORT_SYMBOL_GPL(edac_handlers);

int edac_err_assert = 0;
EXPORT_SYMBOL_GPL(edac_err_assert);

static atomic_t edac_subsys_valid = ATOMIC_INIT(0);

/*
 * called to determine if there is an EDAC driver interested in
 * knowing an event (such as NMI) occurred
 */
int edac_handler_set(void)
{
	if (edac_op_state == EDAC_OPSTATE_POLL)
		return 0;

	return atomic_read(&edac_handlers);
}
EXPORT_SYMBOL_GPL(edac_handler_set);

/*
 * handler for NMI type of interrupts to assert error
 */
void edac_atomic_assert_error(void)
{
	edac_err_assert++;
}
EXPORT_SYMBOL_GPL(edac_atomic_assert_error);

/*
 * sysfs object: /sys/devices/system/edac
 *	need to export to other files
 */
struct bus_type edac_subsys = {
	.name = "edac",
	.dev_name = "edac",
};
EXPORT_SYMBOL_GPL(edac_subsys);

/* return pointer to the 'edac' node in sysfs */
struct bus_type *edac_get_sysfs_subsys(void)
{
	int err = 0;

	if (atomic_read(&edac_subsys_valid))
		goto out;

	/* create the /sys/devices/system/edac directory */
	err = subsys_system_register(&edac_subsys, NULL);
	if (err) {
		printk(KERN_ERR "Error registering toplevel EDAC sysfs dir\n");
		return NULL;
	}

out:
	atomic_inc(&edac_subsys_valid);
	return &edac_subsys;
}
EXPORT_SYMBOL_GPL(edac_get_sysfs_subsys);

void edac_put_sysfs_subsys(void)
{
	/* last user unregisters it */
	if (atomic_dec_and_test(&edac_subsys_valid))
		bus_unregister(&edac_subsys);
}
EXPORT_SYMBOL_GPL(edac_put_sysfs_subsys);
