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
#ifndef _XEN_ACPI_H
#define _XEN_ACPI_H

#include <beep/types.h>

#ifdef CONFIG_XEN_DOM0
#include <asm/xen/hypervisor.h>
#include <xen/xen.h>
#include <beep/acpi.h>

int xen_acpi_notify_hypervisor_state(u8 sleep_state,
				     u32 pm1a_cnt, u32 pm1b_cnd);

static inline void xen_acpi_sleep_register(void)
{
	if (xen_initial_domain())
		acpi_os_set_prepare_sleep(
			&xen_acpi_notify_hypervisor_state);
}
#else
static inline void xen_acpi_sleep_register(void)
{
}
#endif

#endif	/* _XEN_ACPI_H */
