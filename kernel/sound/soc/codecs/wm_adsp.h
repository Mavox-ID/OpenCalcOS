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
#ifndef __WM_ADSP_H
#define __WM_ADSP_H

#include <sound/soc.h>
#include <sound/soc-dapm.h>

#include "wmfw.h"

struct regulator;

struct wm_adsp_region {
	int type;
	unsigned int base;
};

struct wm_adsp {
	const char *part;
	int num;
	int type;
	struct device *dev;
	struct regmap *regmap;

	int base;

	const struct wm_adsp_region *mem;
	int num_mems;

	struct regulator *dvfs;
};

#define WM_ADSP1(wname, num) \
	{ .id = snd_soc_dapm_pga, .name = wname, .reg = SND_SOC_NOPM, \
	.shift = num, .event = wm_adsp1_event, \
	.event_flags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD }

#define WM_ADSP2(wname, num) \
{	.id = snd_soc_dapm_pga, .name = wname, .reg = SND_SOC_NOPM, \
	.shift = num, .event = wm_adsp2_event, \
	.event_flags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD }

int wm_adsp2_init(struct wm_adsp *adsp, bool dvfs);
int wm_adsp1_event(struct snd_soc_dapm_widget *w,
		   struct snd_kcontrol *kcontrol, int event);
int wm_adsp2_event(struct snd_soc_dapm_widget *w,
		   struct snd_kcontrol *kcontrol, int event);

#endif
