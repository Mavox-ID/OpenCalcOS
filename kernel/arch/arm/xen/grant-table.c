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
#include <xen/interface/xen.h>
#include <xen/page.h>
#include <xen/grant_table.h>

int arch_gnttab_map_shared(xen_pfn_t *frames, unsigned long nr_gframes,
			   unsigned long max_nr_gframes,
			   void **__shared)
{
	return -ENOSYS;
}

void arch_gnttab_unmap(void *shared, unsigned long nr_gframes)
{
	return;
}

int arch_gnttab_map_status(uint64_t *frames, unsigned long nr_gframes,
			   unsigned long max_nr_gframes,
			   grant_status_t **__shared)
{
	return -ENOSYS;
}
