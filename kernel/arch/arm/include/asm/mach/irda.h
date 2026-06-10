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
#ifndef __ASM_ARM_MACH_IRDA_H
#define __ASM_ARM_MACH_IRDA_H

struct irda_platform_data {
	int (*startup)(struct device *);
	void (*shutdown)(struct device *);
	int (*set_power)(struct device *, unsigned int state);
	void (*set_speed)(struct device *, unsigned int speed);
};

#endif
