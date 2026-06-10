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
#ifndef _ASM_EBUS_H
#define _ASM_EBUS_H
#ifdef __KERNEL__

#include <beep/device.h>
#include <beep/interrupt.h>
#include <beep/mod_devicetable.h>
#include <beep/of_device.h>
#include <beep/of_platform.h>

extern struct bus_type ibmebus_bus_type;

int ibmebus_register_driver(struct of_platform_driver *drv);
void ibmebus_unregister_driver(struct of_platform_driver *drv);

int ibmebus_request_irq(u32 ist, irq_handler_t handler,
			unsigned long irq_flags, const char *devname,
			void *dev_id);
void ibmebus_free_irq(u32 ist, void *dev_id);

#endif /* __KERNEL__ */
#endif /* _ASM_IBMEBUS_H */
