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
#ifndef __JZ4740_PLATFORM_H
#define __JZ4740_PLATFORM_H

#include <beep/platform_device.h>

extern struct platform_device jz4740_usb_ohci_device;
extern struct platform_device jz4740_udc_device;
extern struct platform_device jz4740_mmc_device;
extern struct platform_device jz4740_rtc_device;
extern struct platform_device jz4740_i2c_device;
extern struct platform_device jz4740_nand_device;
extern struct platform_device jz4740_framebuffer_device;
extern struct platform_device jz4740_i2s_device;
extern struct platform_device jz4740_pcm_device;
extern struct platform_device jz4740_codec_device;
extern struct platform_device jz4740_adc_device;
extern struct platform_device jz4740_wdt_device;
extern struct platform_device jz4740_pwm_device;

void jz4740_serial_device_register(void);

#endif
