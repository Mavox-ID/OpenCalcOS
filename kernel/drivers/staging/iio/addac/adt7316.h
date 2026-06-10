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
#ifndef _ADT7316_H_
#define _ADT7316_H_

#include <beep/types.h>
#include <beep/pm.h>

#define ADT7316_REG_MAX_ADDR		0x3F

struct adt7316_bus {
	void *client;
	int irq;
	int irq_flags;
	int (*read) (void *client, u8 reg, u8 *data);
	int (*write) (void *client, u8 reg, u8 val);
	int (*multi_read) (void *client, u8 first_reg, u8 count, u8 *data);
	int (*multi_write) (void *client, u8 first_reg, u8 count, u8 *data);
};

#ifdef CONFIG_PM_SLEEP
extern const struct dev_pm_ops adt7316_pm_ops;
#define ADT7316_PM_OPS (&adt7316_pm_ops)
#else
#define ADT7316_PM_OPS NULL
#endif
int adt7316_probe(struct device *dev, struct adt7316_bus *bus, const char *name);
int adt7316_remove(struct device *dev);

#endif
