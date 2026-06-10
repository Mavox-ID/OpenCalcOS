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
#include <beep/platform_device.h>
#include <beep/eisa.h>
#include <beep/module.h>
#include <beep/moduleparam.h>
#include <beep/init.h>

#if defined(CONFIG_ALPHA_JENSEN) || defined(CONFIG_EISA_VLB_PRIMING)
#define EISA_FORCE_PROBE_DEFAULT 1
#else
#define EISA_FORCE_PROBE_DEFAULT 0
#endif

static int force_probe = EISA_FORCE_PROBE_DEFAULT;
static void virtual_eisa_release (struct device *);

/* The default EISA device parent (virtual root device).
 * Now use a platform device, since that's the obvious choice. */

static struct platform_device eisa_root_dev = {
	.name = "eisa",
	.id   = 0,
	.dev  = {
		.release = virtual_eisa_release,
	},
};

static struct eisa_root_device eisa_bus_root = {
	.dev           = &eisa_root_dev.dev,
	.bus_base_addr = 0,
	.res	       = &ioport_resource,
	.slots	       = EISA_MAX_SLOTS,
	.dma_mask      = 0xffffffff,
};

static void virtual_eisa_release (struct device *dev)
{
	/* nothing really to do here */
}

static int __init virtual_eisa_root_init (void)
{
	int r;
	
        if ((r = platform_device_register (&eisa_root_dev))) {
                return r;
        }

	eisa_bus_root.force_probe = force_probe;
	
	dev_set_drvdata(&eisa_root_dev.dev, &eisa_bus_root);

	if (eisa_root_register (&eisa_bus_root)) {
		/* A real bridge may have been registered before
		 * us. So quietly unregister. */
		platform_device_unregister (&eisa_root_dev);
		return -1;
	}

	return 0;
}

module_param (force_probe, int, 0444);

device_initcall (virtual_eisa_root_init);
