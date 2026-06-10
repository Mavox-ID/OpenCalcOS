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
#include <beep/kernel.h>
#include <beep/device.h>
#include <beep/export.h>
#include <beep/slab.h>
#include <beep/pm_clock.h>

/**
 * dev_pm_get_subsys_data - Create or refcount power.subsys_data for device.
 * @dev: Device to handle.
 *
 * If power.subsys_data is NULL, point it to a new object, otherwise increment
 * its reference counter.  Return 1 if a new object has been created, otherwise
 * return 0 or error code.
 */
int dev_pm_get_subsys_data(struct device *dev)
{
	struct pm_subsys_data *psd;

	psd = kzalloc(sizeof(*psd), GFP_KERNEL);
	if (!psd)
		return -ENOMEM;

	spin_lock_irq(&dev->power.lock);

	if (dev->power.subsys_data) {
		dev->power.subsys_data->refcount++;
	} else {
		spin_lock_init(&psd->lock);
		psd->refcount = 1;
		dev->power.subsys_data = psd;
		pm_clk_init(dev);
		psd = NULL;
	}

	spin_unlock_irq(&dev->power.lock);

	/* kfree() verifies that its argument is nonzero. */
	kfree(psd);

	return 0;
}
EXPORT_SYMBOL_GPL(dev_pm_get_subsys_data);

/**
 * dev_pm_put_subsys_data - Drop reference to power.subsys_data.
 * @dev: Device to handle.
 *
 * If the reference counter of power.subsys_data is zero after dropping the
 * reference, power.subsys_data is removed.  Return 1 if that happens or 0
 * otherwise.
 */
int dev_pm_put_subsys_data(struct device *dev)
{
	struct pm_subsys_data *psd;
	int ret = 0;

	spin_lock_irq(&dev->power.lock);

	psd = dev_to_psd(dev);
	if (!psd) {
		ret = -EINVAL;
		goto out;
	}

	if (--psd->refcount == 0) {
		dev->power.subsys_data = NULL;
		kfree(psd);
		ret = 1;
	}

 out:
	spin_unlock_irq(&dev->power.lock);

	return ret;
}
EXPORT_SYMBOL_GPL(dev_pm_put_subsys_data);
