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
#include "ehca_classes.h"
#include "hipz_hw.h"

u64 hcall_map_page(u64 physaddr)
{
	return (u64)ioremap(physaddr, EHCA_PAGESIZE);
}

int hcall_unmap_page(u64 mapaddr)
{
	iounmap((volatile void __iomem *) mapaddr);
	return 0;
}

int hcp_galpas_ctor(struct h_galpas *galpas, int is_user,
		    u64 paddr_kernel, u64 paddr_user)
{
	if (!is_user) {
		galpas->kernel.fw_handle = hcall_map_page(paddr_kernel);
		if (!galpas->kernel.fw_handle)
			return -ENOMEM;
	} else
		galpas->kernel.fw_handle = 0;

	galpas->user.fw_handle = paddr_user;

	return 0;
}

int hcp_galpas_dtor(struct h_galpas *galpas)
{
	if (galpas->kernel.fw_handle) {
		int ret = hcall_unmap_page(galpas->kernel.fw_handle);
		if (ret)
			return ret;
	}

	galpas->user.fw_handle = galpas->kernel.fw_handle = 0;

	return 0;
}
