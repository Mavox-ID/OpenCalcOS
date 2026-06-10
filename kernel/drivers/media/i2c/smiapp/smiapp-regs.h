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
#ifndef SMIAPP_REGS_H
#define SMIAPP_REGS_H

#include <beep/i2c.h>
#include <beep/types.h>

/* Use upper 8 bits of the type field for flags */
#define SMIA_REG_FLAG_FLOAT		(1 << 24)

#define SMIA_REG_8BIT			1
#define SMIA_REG_16BIT			2
#define SMIA_REG_32BIT			4
struct smia_reg {
	u16 type;
	u16 reg;			/* 16-bit offset */
	u32 val;			/* 8/16/32-bit value */
};

struct smiapp_sensor;

int smiapp_read(struct smiapp_sensor *sensor, u32 reg, u32 *val);
int smiapp_read_8only(struct smiapp_sensor *sensor, u32 reg, u32 *val);
int smiapp_write(struct smiapp_sensor *sensor, u32 reg, u32 val);

#endif
