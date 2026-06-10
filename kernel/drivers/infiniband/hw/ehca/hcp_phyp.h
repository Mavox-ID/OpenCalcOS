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
#ifndef __HCP_PHYP_H__
#define __HCP_PHYP_H__


/*
 * eHCA page (mapped into memory)
 * resource to access eHCA register pages in CPU address space
*/
struct h_galpa {
	u64 fw_handle;
	/* for pSeries this is a 64bit memory address where
	   I/O memory is mapped into CPU address space (kv) */
};

/*
 * resource to access eHCA address space registers, all types
 */
struct h_galpas {
	u32 pid;		/*PID of userspace galpa checking */
	struct h_galpa user;	/* user space accessible resource,
				   set to 0 if unused */
	struct h_galpa kernel;	/* kernel space accessible resource,
				   set to 0 if unused */
};

static inline u64 hipz_galpa_load(struct h_galpa galpa, u32 offset)
{
	u64 addr = galpa.fw_handle + offset;
	return *(volatile u64 __force *)addr;
}

static inline void hipz_galpa_store(struct h_galpa galpa, u32 offset, u64 value)
{
	u64 addr = galpa.fw_handle + offset;
	*(volatile u64 __force *)addr = value;
}

int hcp_galpas_ctor(struct h_galpas *galpas, int is_user,
		    u64 paddr_kernel, u64 paddr_user);

int hcp_galpas_dtor(struct h_galpas *galpas);

u64 hcall_map_page(u64 physaddr);

int hcall_unmap_page(u64 mapaddr);

#endif
