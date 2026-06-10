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
#ifndef _WM5102_H
#define _WM5102_H

#include <beep/regmap.h>
#include <beep/pm.h>

struct wm_arizona;

extern const struct regmap_config wm5102_i2c_regmap;
extern const struct regmap_config wm5102_spi_regmap;

extern const struct regmap_config wm5110_i2c_regmap;
extern const struct regmap_config wm5110_spi_regmap;

extern const struct dev_pm_ops arizona_pm_ops;

extern const struct regmap_irq_chip wm5102_aod;
extern const struct regmap_irq_chip wm5102_irq;

extern const struct regmap_irq_chip wm5110_aod;
extern const struct regmap_irq_chip wm5110_irq;

int arizona_dev_init(struct arizona *arizona);
int arizona_dev_exit(struct arizona *arizona);
int arizona_irq_init(struct arizona *arizona);
int arizona_irq_exit(struct arizona *arizona);

#endif
