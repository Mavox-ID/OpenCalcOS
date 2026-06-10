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
#ifndef __DRIVERS_USB_CHIPIDEA_DEBUG_H
#define __DRIVERS_USB_CHIPIDEA_DEBUG_H

#ifdef CONFIG_USB_CHIPIDEA_DEBUG
void dbg_interrupt(u32 intmask);
void dbg_done(u8 addr, const u32 token, int status);
void dbg_event(u8 addr, const char *name, int status);
void dbg_queue(u8 addr, const struct usb_request *req, int status);
void dbg_setup(u8 addr, const struct usb_ctrlrequest *req);
int dbg_create_files(struct device *dev);
int dbg_remove_files(struct device *dev);
#else
static inline void dbg_interrupt(u32 intmask)
{
}

static inline void dbg_done(u8 addr, const u32 token, int status)
{
}

static inline void dbg_event(u8 addr, const char *name, int status)
{
}

static inline void dbg_queue(u8 addr, const struct usb_request *req, int status)
{
}

static inline void dbg_setup(u8 addr, const struct usb_ctrlrequest *req)
{
}

static inline int dbg_create_files(struct device *dev)
{
	return 0;
}

static inline int dbg_remove_files(struct device *dev)
{
	return 0;
}
#endif

#endif /* __DRIVERS_USB_CHIPIDEA_DEBUG_H */
