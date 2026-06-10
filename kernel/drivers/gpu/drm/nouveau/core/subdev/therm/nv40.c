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

static int
nv40_sensor_setup(struct nouveau_therm *therm)
{
	struct nouveau_device *device = nv_device(therm);

	/* enable ADC readout and disable the ALARM threshold */
	if (device->chipset >= 0x46) {
		nv_mask(therm, 0x15b8, 0x80000000, 0);
		nv_wr32(therm, 0x15b0, 0x80003fff);
		return nv_rd32(therm, 0x15b4) & 0x3fff;
	} else {
		nv_wr32(therm, 0x15b0, 0xff);
		return nv_rd32(therm, 0x15b4) & 0xff;
	}
}

static int
nv40_temp_get(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;
	struct nouveau_device *device = nv_device(therm);
	struct nvbios_therm_sensor *sensor = &priv->bios_sensor;
	int core_temp;

	if (device->chipset >= 0x46) {
		nv_wr32(therm, 0x15b0, 0x80003fff);
		core_temp = nv_rd32(therm, 0x15b4) & 0x3fff;
	} else {
		nv_wr32(therm, 0x15b0, 0xff);
		core_temp = nv_rd32(therm, 0x15b4) & 0xff;
	}

	/* Setup the sensor if the temperature is 0 */
	if (core_temp == 0)
		core_temp = nv40_sensor_setup(therm);

	if (sensor->slope_div == 0)
		sensor->slope_div = 1;
	if (sensor->offset_den == 0)
		sensor->offset_den = 1;
	if (sensor->slope_mult < 1)
		sensor->slope_mult = 1;

	core_temp = core_temp * sensor->slope_mult / sensor->slope_div;
	core_temp = core_temp + sensor->offset_num / sensor->offset_den;
	core_temp = core_temp + sensor->offset_constant - 8;

	return core_temp;
}

int
nv40_fan_pwm_get(struct nouveau_therm *therm, int line, u32 *divs, u32 *duty)
{
	if (line == 2) {
		u32 reg = nv_rd32(therm, 0x0010f0);
		if (reg & 0x80000000) {
			*duty = (reg & 0x7fff0000) >> 16;
			*divs = (reg & 0x00007fff);
			return 0;
		}
	} else
	if (line == 9) {
		u32 reg = nv_rd32(therm, 0x0015f4);
		if (reg & 0x80000000) {
			*divs = nv_rd32(therm, 0x0015f8);
			*duty = (reg & 0x7fffffff);
			return 0;
		}
	} else {
		nv_error(therm, "unknown pwm ctrl for gpio %d\n", line);
		return -ENODEV;
	}

	return -EINVAL;
}

int
nv40_fan_pwm_set(struct nouveau_therm *therm, int line, u32 divs, u32 duty)
{
	if (line == 2) {
		nv_wr32(therm, 0x0010f0, 0x80000000 | (duty << 16) | divs);
	} else
	if (line == 9) {
		nv_wr32(therm, 0x0015f8, divs);
		nv_wr32(therm, 0x0015f4, duty | 0x80000000);
	} else {
		nv_error(therm, "unknown pwm ctrl for gpio %d\n", line);
		return -ENODEV;
	}

	return 0;
}

static int
nv40_therm_ctor(struct nouveau_object *parent,
		   struct nouveau_object *engine,
		   struct nouveau_oclass *oclass, void *data, u32 size,
		   struct nouveau_object **pobject)
{
	struct nouveau_therm_priv *priv;
	struct nouveau_therm *therm;
	int ret;

	ret = nouveau_therm_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	therm = (void *) priv;
	if (ret)
		return ret;

	nouveau_therm_ic_ctor(therm);
	nouveau_therm_sensor_ctor(therm);
	nouveau_therm_fan_ctor(therm);

	priv->fan.pwm_get = nv40_fan_pwm_get;
	priv->fan.pwm_set = nv40_fan_pwm_set;

	therm->temp_get = nv40_temp_get;
	therm->fan_get = nouveau_therm_fan_user_get;
	therm->fan_set = nouveau_therm_fan_user_set;
	therm->fan_sense = nouveau_therm_fan_sense;
	therm->attr_get = nouveau_therm_attr_get;
	therm->attr_set = nouveau_therm_attr_set;

	return 0;
}

struct nouveau_oclass
nv40_therm_oclass = {
	.handle = NV_SUBDEV(THERM, 0x40),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv40_therm_ctor,
		.dtor = _nouveau_therm_dtor,
		.init = nouveau_therm_init,
		.fini = nouveau_therm_fini,
	},
};