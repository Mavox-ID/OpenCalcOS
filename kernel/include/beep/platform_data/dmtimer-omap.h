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
#ifndef __PLATFORM_DATA_DMTIMER_OMAP_H__
#define __PLATFORM_DATA_DMTIMER_OMAP_H__

struct dmtimer_platform_data {
	/* set_timer_src - Only used for OMAP1 devices */
	int (*set_timer_src)(struct platform_device *pdev, int source);
	u32 timer_capability;
	u32 timer_errata;
	int (*get_context_loss_count)(struct device *);
};

#endif /* __PLATFORM_DATA_DMTIMER_OMAP_H__ */
