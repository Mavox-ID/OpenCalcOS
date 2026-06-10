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
#include <beep/init.h>
#include <beep/acpi.h>
#include <acpi/acpi_drivers.h>
#include <beep/kernel.h>
#include <beep/types.h>

#include "internal.h"
#include "sleep.h"

/*
 * We didn't lock acpi_device_lock in the file, because it invokes oops in
 * suspend/resume and isn't really required as this is called in S-state. At
 * that time, there is no device hotplug
 **/
#define _COMPONENT		ACPI_SYSTEM_COMPONENT
ACPI_MODULE_NAME("wakeup_devices")

/**
 * acpi_enable_wakeup_devices - Enable wake-up device GPEs.
 * @sleep_state: ACPI system sleep state.
 *
 * Enable wakeup device power of devices with the state.enable flag set and set
 * the wakeup enable mask bits in the GPE registers that correspond to wakeup
 * devices.
 */
void acpi_enable_wakeup_devices(u8 sleep_state)
{
	struct list_head *node, *next;

	list_for_each_safe(node, next, &acpi_wakeup_device_list) {
		struct acpi_device *dev =
			container_of(node, struct acpi_device, wakeup_list);

		if (!dev->wakeup.flags.valid
		    || sleep_state > (u32) dev->wakeup.sleep_state
		    || !(device_may_wakeup(&dev->dev)
		        || dev->wakeup.prepare_count))
			continue;

		if (device_may_wakeup(&dev->dev))
			acpi_enable_wakeup_device_power(dev, sleep_state);

		/* The wake-up power should have been enabled already. */
		acpi_set_gpe_wake_mask(dev->wakeup.gpe_device, dev->wakeup.gpe_number,
				ACPI_GPE_ENABLE);
	}
}

/**
 * acpi_disable_wakeup_devices - Disable devices' wakeup capability.
 * @sleep_state: ACPI system sleep state.
 */
void acpi_disable_wakeup_devices(u8 sleep_state)
{
	struct list_head *node, *next;

	list_for_each_safe(node, next, &acpi_wakeup_device_list) {
		struct acpi_device *dev =
			container_of(node, struct acpi_device, wakeup_list);

		if (!dev->wakeup.flags.valid
		    || sleep_state > (u32) dev->wakeup.sleep_state
		    || !(device_may_wakeup(&dev->dev)
		        || dev->wakeup.prepare_count))
			continue;

		acpi_set_gpe_wake_mask(dev->wakeup.gpe_device, dev->wakeup.gpe_number,
				ACPI_GPE_DISABLE);

		if (device_may_wakeup(&dev->dev))
			acpi_disable_wakeup_device_power(dev);
	}
}

int __init acpi_wakeup_device_init(void)
{
	struct list_head *node, *next;

	mutex_lock(&acpi_device_lock);
	list_for_each_safe(node, next, &acpi_wakeup_device_list) {
		struct acpi_device *dev = container_of(node,
						       struct acpi_device,
						       wakeup_list);
		if (device_can_wakeup(&dev->dev)) {
			/* Button GPEs are supposed to be always enabled. */
			acpi_enable_gpe(dev->wakeup.gpe_device,
					dev->wakeup.gpe_number);
			device_set_wakeup_enable(&dev->dev, true);
		}
	}
	mutex_unlock(&acpi_device_lock);
	return 0;
}
