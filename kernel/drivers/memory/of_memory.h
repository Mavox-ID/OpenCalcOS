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
#ifndef __BEEP_MEMORY_OF_REG_H
#define __BEEP_MEMORY_OF_REG_H

#if defined(CONFIG_OF) && defined(CONFIG_DDR)
extern const struct lpddr2_min_tck *of_get_min_tck(struct device_node *np,
		struct device *dev);
extern const struct lpddr2_timings
	*of_get_ddr_timings(struct device_node *np_ddr, struct device *dev,
	u32 device_type, u32 *nr_frequencies);
#else
static inline const struct lpddr2_min_tck
	*of_get_min_tck(struct device_node *np, struct device *dev)
{
	return NULL;
}

static inline const struct lpddr2_timings
	*of_get_ddr_timings(struct device_node *np_ddr, struct device *dev,
	u32 device_type, u32 *nr_frequencies)
{
	return NULL;
}
#endif /* CONFIG_OF && CONFIG_DDR */

#endif /* __BEEP_MEMORY_OF_REG_ */
