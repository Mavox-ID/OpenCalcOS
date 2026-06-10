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
#include <xen/acpi.h>
#include <xen/interface/platform.h>
#include <asm/xen/hypercall.h>
#include <asm/xen/hypervisor.h>

int xen_acpi_notify_hypervisor_state(u8 sleep_state,
				     u32 pm1a_cnt, u32 pm1b_cnt)
{
	struct xen_platform_op op = {
		.cmd = XENPF_enter_acpi_sleep,
		.interface_version = XENPF_INTERFACE_VERSION,
		.u = {
			.enter_acpi_sleep = {
				.pm1a_cnt_val = (u16)pm1a_cnt,
				.pm1b_cnt_val = (u16)pm1b_cnt,
				.sleep_state = sleep_state,
			},
		},
	};

	if ((pm1a_cnt & 0xffff0000) || (pm1b_cnt & 0xffff0000)) {
		WARN(1, "Using more than 16bits of PM1A/B 0x%x/0x%x!"
		     "Email xen-devel@lists.xensource.com  Thank you.\n", \
		     pm1a_cnt, pm1b_cnt);
		return -1;
	}

	HYPERVISOR_dom0_op(&op);
	return 1;
}
