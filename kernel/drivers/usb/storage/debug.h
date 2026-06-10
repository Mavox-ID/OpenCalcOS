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
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <beep/kernel.h>

#define USB_STORAGE "usb-storage: "

#ifdef CONFIG_USB_STORAGE_DEBUG
void usb_stor_show_command(struct scsi_cmnd *srb);
void usb_stor_show_sense( unsigned char key,
		unsigned char asc, unsigned char ascq );
#define US_DEBUGP(x...) printk( KERN_DEBUG USB_STORAGE x )
#define US_DEBUGPX(x...) printk( x )
#define US_DEBUG(x) x 
#else
#define US_DEBUGP(x...)
#define US_DEBUGPX(x...)
#define US_DEBUG(x)
#endif

#endif
