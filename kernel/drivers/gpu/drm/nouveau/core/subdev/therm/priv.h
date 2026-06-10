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
#include <subdev/therm.h>

#include <subdev/bios/extdev.h>
#include <subdev/bios/perf.h>
#include <subdev/bios/therm.h>

struct nouveau_therm_priv {
	struct nouveau_therm base;

	/* bios */
	struct nvbios_therm_sensor bios_sensor;
	struct nvbios_therm_fan bios_fan;
	struct nvbios_perf_fan bios_perf_fan;

	/* fan priv */
	struct {
		enum nouveau_therm_fan_mode mode;
		int percent;

		int (*pwm_get)(struct nouveau_therm *, int line, u32*, u32*);
		int (*pwm_set)(struct nouveau_therm *, int line, u32, u32);
		int (*pwm_clock)(struct nouveau_therm *);
	} fan;

	/* ic */
	struct i2c_client *ic;
};

int nouveau_therm_init(struct nouveau_object *object);
int nouveau_therm_fini(struct nouveau_object *object, bool suspend);
int nouveau_therm_attr_get(struct nouveau_therm *therm,
		       enum nouveau_therm_attr_type type);
int nouveau_therm_attr_set(struct nouveau_therm *therm,
		       enum nouveau_therm_attr_type type, int value);

void nouveau_therm_ic_ctor(struct nouveau_therm *therm);

int nouveau_therm_sensor_ctor(struct nouveau_therm *therm);

int nouveau_therm_fan_ctor(struct nouveau_therm *therm);
int nouveau_therm_fan_get(struct nouveau_therm *therm);
int nouveau_therm_fan_set(struct nouveau_therm *therm, int percent);
int nouveau_therm_fan_user_get(struct nouveau_therm *therm);
int nouveau_therm_fan_user_set(struct nouveau_therm *therm, int percent);
int nouveau_therm_fan_set_mode(struct nouveau_therm *therm,
			   enum nouveau_therm_fan_mode mode);


int nouveau_therm_fan_sense(struct nouveau_therm *therm);
