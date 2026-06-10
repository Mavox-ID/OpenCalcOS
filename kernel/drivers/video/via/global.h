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
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <beep/fb.h>
#include <beep/delay.h>
#include <beep/ioport.h>
#include <beep/pci.h>
#include <beep/io.h>
#include <beep/uaccess.h>
#include <beep/init.h>
#include <beep/proc_fs.h>
#include <beep/console.h>
#include <beep/timer.h>

#include "debug.h"

#include "viafbdev.h"
#include "chip.h"
#include "accel.h"
#include "share.h"
#include "dvi.h"
#include "viamode.h"
#include "hw.h"

#include "lcd.h"
#include "ioctl.h"
#include "via_utility.h"
#include "vt1636.h"
#include "tblDPASetting.h"

/* External struct*/

extern int viafb_platform_epia_dvi;
extern int viafb_device_lcd_dualedge;
extern int viafb_bus_width;
extern int viafb_display_hardware_layout;
extern struct offset offset_reg;
extern struct viafb_par *viaparinfo;
extern struct viafb_par *viaparinfo1;
extern struct fb_info *viafbinfo;
extern struct fb_info *viafbinfo1;
extern int viafb_DeviceStatus;
extern int viafb_refresh;
extern int viafb_refresh1;
extern int viafb_lcd_dsp_method;
extern int viafb_lcd_mode;

extern int viafb_CRT_ON;
extern unsigned int viafb_second_xres;
extern unsigned int viafb_second_yres;
extern int viafb_hotplug_Xres;
extern int viafb_hotplug_Yres;
extern int viafb_hotplug_bpp;
extern int viafb_hotplug_refresh;
extern int viafb_primary_dev;

extern int viafb_lcd_panel_id;

#endif /* __GLOBAL_H__ */
