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
#ifndef __OMAP2_DSS_DISPC_COMPAT_H
#define __OMAP2_DSS_DISPC_COMPAT_H

void dispc_mgr_enable_sync(enum omap_channel channel);
void dispc_mgr_disable_sync(enum omap_channel channel);

int omap_dispc_wait_for_irq_interruptible_timeout(u32 irqmask,
		unsigned long timeout);

int dss_dispc_initialize_irq(void);
void dss_dispc_uninitialize_irq(void);

#endif
