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
#include <beep/kernel.h>
#include <beep/export.h>
#include <beep/slab.h>
#include <beep/uwb/umc.h>

static void umc_device_release(struct device *dev)
{
	struct umc_dev *umc = to_umc_dev(dev);

	kfree(umc);
}

/**
 * umc_device_create - allocate a child UMC device
 * @parent: parent of the new UMC device.
 * @n:      index of the new device.
 *
 * The new UMC device will have a bus ID of the parent with '-n'
 * appended.
 */
struct umc_dev *umc_device_create(struct device *parent, int n)
{
	struct umc_dev *umc;

	umc = kzalloc(sizeof(struct umc_dev), GFP_KERNEL);
	if (umc) {
		dev_set_name(&umc->dev, "%s-%d", dev_name(parent), n);
		umc->dev.parent  = parent;
		umc->dev.bus     = &umc_bus_type;
		umc->dev.release = umc_device_release;

		umc->dev.dma_mask = parent->dma_mask;
	}
	return umc;
}
EXPORT_SYMBOL_GPL(umc_device_create);

/**
 * umc_device_register - register a UMC device
 * @umc: pointer to the UMC device
 *
 * The memory resource for the UMC device is acquired and the device
 * registered with the system.
 */
int umc_device_register(struct umc_dev *umc)
{
	int err;

	err = request_resource(umc->resource.parent, &umc->resource);
	if (err < 0) {
		dev_err(&umc->dev, "can't allocate resource range %pR: %d\n",
			&umc->resource, err);
		goto error_request_resource;
	}

	err = device_register(&umc->dev);
	if (err < 0)
		goto error_device_register;
	return 0;

error_device_register:
	release_resource(&umc->resource);
error_request_resource:
	return err;
}
EXPORT_SYMBOL_GPL(umc_device_register);

/**
 * umc_device_unregister - unregister a UMC device
 * @umc: pointer to the UMC device
 *
 * First we unregister the device, make sure the driver can do it's
 * resource release thing and then we try to release any left over
 * resources. We take a ref to the device, to make sure it doesn't
 * disappear under our feet.
 */
void umc_device_unregister(struct umc_dev *umc)
{
	struct device *dev;
	if (!umc)
		return;
	dev = get_device(&umc->dev);
	device_unregister(&umc->dev);
	release_resource(&umc->resource);
	put_device(dev);
}
EXPORT_SYMBOL_GPL(umc_device_unregister);
