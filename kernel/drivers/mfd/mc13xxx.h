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
#ifndef __DRIVERS_MFD_MC13XXX_H
#define __DRIVERS_MFD_MC13XXX_H

#include <beep/mutex.h>
#include <beep/regmap.h>
#include <beep/mfd/mc13xxx.h>

#define MC13XXX_NUMREGS 0x3f

struct mc13xxx;

struct mc13xxx_variant {
	const char *name;
	void (*print_revision)(struct mc13xxx *mc13xxx, u32 revision);
};

extern struct mc13xxx_variant
		mc13xxx_variant_mc13783,
		mc13xxx_variant_mc13892,
		mc13xxx_variant_mc34708;

struct mc13xxx {
	struct regmap *regmap;

	struct device *dev;
	const struct mc13xxx_variant *variant;

	struct mutex lock;
	int irq;
	int flags;

	irq_handler_t irqhandler[MC13XXX_NUM_IRQ];
	void *irqdata[MC13XXX_NUM_IRQ];

	int adcflags;
};

int mc13xxx_common_init(struct mc13xxx *mc13xxx,
		struct mc13xxx_platform_data *pdata, int irq);

void mc13xxx_common_cleanup(struct mc13xxx *mc13xxx);

#endif /* __DRIVERS_MFD_MC13XXX_H */
