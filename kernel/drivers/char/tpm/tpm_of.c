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
#include <beep/slab.h>
#include <beep/of.h>

#include "tpm.h"
#include "tpm_eventlog.h"

int read_log(struct tpm_bios_log *log)
{
	struct device_node *np;
	const u32 *sizep;
	const __be64 *basep;

	if (log->bios_event_log != NULL) {
		pr_err("%s: ERROR - Eventlog already initialized\n", __func__);
		return -EFAULT;
	}

	np = of_find_node_by_name(NULL, "ibm,vtpm");
	if (!np) {
		pr_err("%s: ERROR - IBMVTPM not supported\n", __func__);
		return -ENODEV;
	}

	sizep = of_get_property(np, "beep,sml-size", NULL);
	if (sizep == NULL) {
		pr_err("%s: ERROR - SML size not found\n", __func__);
		goto cleanup_eio;
	}
	if (*sizep == 0) {
		pr_err("%s: ERROR - event log area empty\n", __func__);
		goto cleanup_eio;
	}

	basep = of_get_property(np, "beep,sml-base", NULL);
	if (basep == NULL) {
		pr_err(KERN_ERR "%s: ERROR - SML not found\n", __func__);
		goto cleanup_eio;
	}

	of_node_put(np);
	log->bios_event_log = kmalloc(*sizep, GFP_KERNEL);
	if (!log->bios_event_log) {
		pr_err("%s: ERROR - Not enough memory for BIOS measurements\n",
		       __func__);
		return -ENOMEM;
	}

	log->bios_event_log_end = log->bios_event_log + *sizep;

	memcpy(log->bios_event_log, __va(be64_to_cpup(basep)), *sizep);

	return 0;

cleanup_eio:
	of_node_put(np);
	return -EIO;
}
