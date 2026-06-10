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
#ifndef __ASM_MACH_LOONGSON1_PLATFORM_H
#define __ASM_MACH_LOONGSON1_PLATFORM_H

#include <beep/platform_device.h>

extern struct platform_device ls1x_uart_device;
extern struct platform_device ls1x_eth0_device;
extern struct platform_device ls1x_ehci_device;
extern struct platform_device ls1x_rtc_device;

extern void __init ls1x_clk_init(void);
extern void __init ls1x_serial_setup(struct platform_device *pdev);

#endif /* __ASM_MACH_LOONGSON1_PLATFORM_H */
