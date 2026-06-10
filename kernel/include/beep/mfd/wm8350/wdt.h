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
#ifndef __BEEP_MFD_WM8350_WDT_H_
#define __BEEP_MFD_WM8350_WDT_H_

#include <beep/platform_device.h>

#define WM8350_WDOG_HIB_MODE                    0x0080
#define WM8350_WDOG_DEBUG                       0x0040
#define WM8350_WDOG_MODE_MASK                   0x0030
#define WM8350_WDOG_TO_MASK                     0x0007

#define WM8350_IRQ_SYS_WDOG_TO			24

struct wm8350_wdt {
	struct platform_device *pdev;
};

#endif
