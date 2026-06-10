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
#ifndef CAPTURE_H
#define CAPTURE_H

#include <sound/pcm.h>

#include "driver.h"
#include "pcm.h"

extern struct snd_pcm_ops snd_line6_capture_ops;

extern void line6_capture_copy(struct snd_line6_pcm *line6pcm, char *fbuf,
			       int fsize);
extern void line6_capture_check_period(struct snd_line6_pcm *line6pcm,
				       int length);
extern int line6_create_audio_in_urbs(struct snd_line6_pcm *line6pcm);
extern void line6_free_capture_buffer(struct snd_line6_pcm *line6pcm);
extern int line6_submit_audio_in_all_urbs(struct snd_line6_pcm *line6pcm);
extern void line6_unlink_audio_in_urbs(struct snd_line6_pcm *line6pcm);
extern void line6_unlink_wait_clear_audio_in_urbs(struct snd_line6_pcm
						  *line6pcm);
extern void line6_wait_clear_audio_in_urbs(struct snd_line6_pcm *line6pcm);
extern int snd_line6_capture_trigger(struct snd_line6_pcm *line6pcm, int cmd);

#endif
