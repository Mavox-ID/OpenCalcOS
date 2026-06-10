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
#ifndef __ARCH_ARM_MACH_MSM_DEVICES_H
#define __ARCH_ARM_MACH_MSM_DEVICES_H

#include <beep/clkdev.h>

#include "clock.h"

extern struct platform_device msm_device_uart1;
extern struct platform_device msm_device_uart2;
extern struct platform_device msm_device_uart3;

extern struct platform_device msm8960_device_uart_gsbi2;
extern struct platform_device msm8960_device_uart_gsbi5;

extern struct platform_device msm_device_sdc1;
extern struct platform_device msm_device_sdc2;
extern struct platform_device msm_device_sdc3;
extern struct platform_device msm_device_sdc4;

extern struct platform_device msm_device_hsusb;
extern struct platform_device msm_device_otg;
extern struct platform_device msm_device_hsusb_host;

extern struct platform_device msm_device_i2c;

extern struct platform_device msm_device_smd;

extern struct platform_device msm_device_nand;

extern struct platform_device msm_device_mddi0;
extern struct platform_device msm_device_mddi1;
extern struct platform_device msm_device_mdp;

extern struct clk_lookup msm_clocks_7x01a[];
extern unsigned msm_num_clocks_7x01a;

extern struct clk_lookup msm_clocks_7x30[];
extern unsigned msm_num_clocks_7x30;

extern struct clk_lookup msm_clocks_8x50[];
extern unsigned msm_num_clocks_8x50;

#endif
