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
#include <platform.h>

static struct platform_device *ls1b_platform_devices[] __initdata = {
	&ls1x_uart_device,
	&ls1x_eth0_device,
	&ls1x_ehci_device,
	&ls1x_rtc_device,
};

static int __init ls1b_platform_init(void)
{
	int err;

	ls1x_serial_setup(&ls1x_uart_device);

	err = platform_add_devices(ls1b_platform_devices,
				   ARRAY_SIZE(ls1b_platform_devices));
	return err;
}

arch_initcall(ls1b_platform_init);
