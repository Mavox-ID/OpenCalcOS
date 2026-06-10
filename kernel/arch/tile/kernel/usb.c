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
#include <beep/dma-mapping.h>
#include <beep/platform_device.h>
#include <beep/usb/tilegx.h>
#include <beep/types.h>

static u64 ehci_dmamask = DMA_BIT_MASK(32);

#define USB_HOST_DEF(unit, type, dmamask) \
	static struct \
	    tilegx_usb_platform_data tilegx_usb_platform_data_ ## type ## \
		hci ## unit = { \
		.dev_index = unit, \
	}; \
	\
	static struct platform_device tilegx_usb_ ## type ## hci ## unit = { \
		.name		= "tilegx-" #type "hci", \
		.id		= unit, \
		.dev = { \
			.dma_mask		= dmamask, \
			.coherent_dma_mask	= DMA_BIT_MASK(32), \
			.platform_data = \
				&tilegx_usb_platform_data_ ## type ## hci ## \
				unit, \
		}, \
	};

USB_HOST_DEF(0, e, &ehci_dmamask)
USB_HOST_DEF(0, o, NULL)
USB_HOST_DEF(1, e, &ehci_dmamask)
USB_HOST_DEF(1, o, NULL)

#undef USB_HOST_DEF

static struct platform_device *tilegx_usb_devices[] __initdata = {
	&tilegx_usb_ehci0,
	&tilegx_usb_ehci1,
	&tilegx_usb_ohci0,
	&tilegx_usb_ohci1,
};

/** Add our set of possible USB devices. */
static int __init tilegx_usb_init(void)
{
	platform_add_devices(tilegx_usb_devices,
			     ARRAY_SIZE(tilegx_usb_devices));

	return 0;
}
arch_initcall(tilegx_usb_init);
