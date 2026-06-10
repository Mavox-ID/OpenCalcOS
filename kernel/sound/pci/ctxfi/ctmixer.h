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
#ifndef CTMIXER_H
#define CTMIXER_H

#include "ctatc.h"
#include "ctresource.h"

#define INIT_VOL	0x1c00

enum MIXER_PORT_T {
	MIX_WAVE_FRONT,
	MIX_WAVE_REAR,
	MIX_WAVE_CENTLFE,
	MIX_WAVE_SURROUND,
	MIX_SPDIF_OUT,
	MIX_PCMO_FRONT,
	MIX_MIC_IN,
	MIX_LINE_IN,
	MIX_SPDIF_IN,
	MIX_PCMI_FRONT,
	MIX_PCMI_REAR,
	MIX_PCMI_CENTLFE,
	MIX_PCMI_SURROUND,

	NUM_MIX_PORTS
};

/* alsa mixer descriptor */
struct ct_mixer {
	struct ct_atc *atc;

	void **amixers;		/* amixer resources for volume control */
	void **sums;		/* sum resources for signal collection */
	unsigned int switch_state; /* A bit-map to indicate state of switches */

	int (*get_output_ports)(struct ct_mixer *mixer, enum MIXER_PORT_T type,
				  struct rsc **rleft, struct rsc **rright);

	int (*set_input_left)(struct ct_mixer *mixer,
			      enum MIXER_PORT_T type, struct rsc *rsc);
	int (*set_input_right)(struct ct_mixer *mixer,
			       enum MIXER_PORT_T type, struct rsc *rsc);
#ifdef CONFIG_PM_SLEEP
	int (*resume)(struct ct_mixer *mixer);
#endif
};

int ct_alsa_mix_create(struct ct_atc *atc,
		       enum CTALSADEVS device,
		       const char *device_name);
int ct_mixer_create(struct ct_atc *atc, struct ct_mixer **rmixer);
int ct_mixer_destroy(struct ct_mixer *mixer);

#endif /* CTMIXER_H */
