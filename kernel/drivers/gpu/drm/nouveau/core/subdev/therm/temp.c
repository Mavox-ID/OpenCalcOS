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
#include "priv.h"

#include <core/object.h>
#include <core/device.h>

#include <subdev/bios.h>

static void
nouveau_therm_temp_set_defaults(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;

	priv->bios_sensor.slope_mult = 1;
	priv->bios_sensor.slope_div = 1;
	priv->bios_sensor.offset_num = 0;
	priv->bios_sensor.offset_den = 1;
	priv->bios_sensor.offset_constant = 0;

	priv->bios_sensor.thrs_fan_boost.temp = 90;
	priv->bios_sensor.thrs_fan_boost.hysteresis = 3;

	priv->bios_sensor.thrs_down_clock.temp = 95;
	priv->bios_sensor.thrs_down_clock.hysteresis = 3;

	priv->bios_sensor.thrs_critical.temp = 105;
	priv->bios_sensor.thrs_critical.hysteresis = 5;

	priv->bios_sensor.thrs_shutdown.temp = 135;
	priv->bios_sensor.thrs_shutdown.hysteresis = 5; /*not that it matters */
}


static void
nouveau_therm_temp_safety_checks(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;

	if (!priv->bios_sensor.slope_div)
		priv->bios_sensor.slope_div = 1;
	if (!priv->bios_sensor.offset_den)
		priv->bios_sensor.offset_den = 1;
}

int
nouveau_therm_sensor_ctor(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;
	struct nouveau_bios *bios = nouveau_bios(therm);

	nouveau_therm_temp_set_defaults(therm);
	if (nvbios_therm_sensor_parse(bios, NVBIOS_THERM_DOMAIN_CORE,
				      &priv->bios_sensor))
		nv_error(therm, "nvbios_therm_sensor_parse failed\n");
	nouveau_therm_temp_safety_checks(therm);

	return 0;
}
