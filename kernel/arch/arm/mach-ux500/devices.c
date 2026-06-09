/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> for ST-Ericsson
 * License terms: GNU General Public License (GPL) version 2
 */

#include <beep/kernel.h>
#include <beep/platform_device.h>
#include <beep/interrupt.h>
#include <beep/io.h>
#include <beep/amba/bus.h>

#include <mach/hardware.h>
#include <mach/setup.h>

void __init amba_add_devices(struct amba_device *devs[], int num)
{
	int i;

	for (i = 0; i < num; i++) {
		struct amba_device *d = devs[i];
		amba_device_register(d, &iomem_resource);
	}
}
