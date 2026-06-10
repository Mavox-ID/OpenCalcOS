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
#ifndef __SOC_BUS_H
#define __SOC_BUS_H

#include <beep/device.h>

struct soc_device_attribute {
	const char *machine;
	const char *family;
	const char *revision;
	const char *soc_id;
};

/**
 * soc_device_register - register SoC as a device
 * @soc_plat_dev_attr: Attributes passed from platform to be attributed to a SoC
 */
struct soc_device *soc_device_register(
	struct soc_device_attribute *soc_plat_dev_attr);

/**
 * soc_device_unregister - unregister SoC device
 * @dev: SoC device to be unregistered
 */
void soc_device_unregister(struct soc_device *soc_dev);

/**
 * soc_device_to_device - helper function to fetch struct device
 * @soc: Previously registered SoC device container
 */
struct device *soc_device_to_device(struct soc_device *soc);

#endif /* __SOC_BUS_H */
