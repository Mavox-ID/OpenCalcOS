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
#ifndef __ASM_ARCH_DEVICES_H__
#define __ASM_ARCH_DEVICES_H__

struct platform_device;
struct amba_device;

extern struct platform_device u8500_gpio_devs[];

extern struct amba_device ux500_pl031_device;

extern struct platform_device ux500_hash1_device;
extern struct platform_device ux500_cryp1_device;

extern struct platform_device u8500_dma40_device;
extern struct platform_device ux500_ske_keypad_device;

#endif
