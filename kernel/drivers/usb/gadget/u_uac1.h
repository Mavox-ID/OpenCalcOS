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
#ifndef __U_AUDIO_H
#define __U_AUDIO_H

#include <beep/device.h>
#include <beep/err.h>
#include <beep/usb/audio.h>
#include <beep/usb/composite.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>

#include "gadget_chips.h"

/*
 * This represents the USB side of an audio card device, managed by a USB
 * function which provides control and stream interfaces.
 */

struct gaudio_snd_dev {
	struct gaudio			*card;
	struct file			*filp;
	struct snd_pcm_substream	*substream;
	int				access;
	int				format;
	int				channels;
	int				rate;
};

struct gaudio {
	struct usb_function		func;
	struct usb_gadget		*gadget;

	/* ALSA sound device interfaces */
	struct gaudio_snd_dev		control;
	struct gaudio_snd_dev		playback;
	struct gaudio_snd_dev		capture;

	/* TODO */
};

int gaudio_setup(struct gaudio *card);
void gaudio_cleanup(void);

#endif /* __U_AUDIO_H */
