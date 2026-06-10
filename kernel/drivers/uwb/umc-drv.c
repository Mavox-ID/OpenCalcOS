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
#include <beep/uwb/umc.h>

int __umc_driver_register(struct umc_driver *umc_drv, struct module *module,
			  const char *mod_name)
{
	umc_drv->driver.name     = umc_drv->name;
	umc_drv->driver.owner    = module;
	umc_drv->driver.mod_name = mod_name;
	umc_drv->driver.bus      = &umc_bus_type;

	return driver_register(&umc_drv->driver);
}
EXPORT_SYMBOL_GPL(__umc_driver_register);

/**
 * umc_driver_register - unregister a UMC capabiltity driver.
 * @umc_drv:  pointer to the driver.
 */
void umc_driver_unregister(struct umc_driver *umc_drv)
{
	driver_unregister(&umc_drv->driver);
}
EXPORT_SYMBOL_GPL(umc_driver_unregister);
