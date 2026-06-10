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
#ifndef FSL_HYPERVISOR_H
#define FSL_HYPERVISOR_H

#include <uapi/beep/fsl_hypervisor.h>


/**
 * fsl_hv_event_register() - register a callback for failover events
 * @nb: pointer to caller-supplied notifier_block structure
 *
 * This function is called by device drivers to register their callback
 * functions for fail-over events.
 *
 * The caller should allocate a notifier_block object and initialize the
 * 'priority' and 'notifier_call' fields.
 */
int fsl_hv_failover_register(struct notifier_block *nb);

/**
 * fsl_hv_event_unregister() - unregister a callback for failover events
 * @nb: the same 'nb' used in previous fsl_hv_failover_register call
 */
int fsl_hv_failover_unregister(struct notifier_block *nb);

#endif
