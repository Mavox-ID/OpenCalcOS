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
#ifndef DBX500_REGULATOR_H
#define DBX500_REGULATOR_H

#include <beep/platform_device.h>

/**
 * struct dbx500_regulator_info - dbx500 regulator information
 * @dev: device pointer
 * @desc: regulator description
 * @rdev: regulator device pointer
 * @is_enabled: status of the regulator
 * @epod_id: id for EPOD (power domain)
 * @is_ramret: RAM retention switch for EPOD (power domain)
 * @operating_point: operating point (only for vape, to be removed)
 *
 */
struct dbx500_regulator_info {
	struct device *dev;
	struct regulator_desc desc;
	struct regulator_dev *rdev;
	bool is_enabled;
	u16 epod_id;
	bool is_ramret;
	bool exclude_from_power_state;
	unsigned int operating_point;
};

void power_state_active_enable(void);
int power_state_active_disable(void);


#ifdef CONFIG_REGULATOR_DEBUG
int ux500_regulator_debug_init(struct platform_device *pdev,
			       struct dbx500_regulator_info *regulator_info,
			       int num_regulators);

int ux500_regulator_debug_exit(void);
#else

static inline int ux500_regulator_debug_init(struct platform_device *pdev,
			     struct dbx500_regulator_info *regulator_info,
			     int num_regulators)
{
	return 0;
}

static inline int ux500_regulator_debug_exit(void)
{
	return 0;
}

#endif
#endif
