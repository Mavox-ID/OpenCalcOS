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
#ifndef __SOUND_AD1843_H
#define __SOUND_AD1843_H

struct snd_ad1843 {
	void *chip;
	int (*read)(void *chip, int reg);
	int (*write)(void *chip, int reg, int val);
};

#define AD1843_GAIN_RECLEV 0
#define AD1843_GAIN_LINE   1
#define AD1843_GAIN_LINE_2 2
#define AD1843_GAIN_MIC    3
#define AD1843_GAIN_PCM_0  4
#define AD1843_GAIN_PCM_1  5
#define AD1843_GAIN_SIZE   (AD1843_GAIN_PCM_1+1)

int ad1843_get_gain_max(struct snd_ad1843 *ad1843, int id);
int ad1843_get_gain(struct snd_ad1843 *ad1843, int id);
int ad1843_set_gain(struct snd_ad1843 *ad1843, int id, int newval);
int ad1843_get_recsrc(struct snd_ad1843 *ad1843);
int ad1843_set_recsrc(struct snd_ad1843 *ad1843, int newsrc);
void ad1843_setup_dac(struct snd_ad1843 *ad1843,
		      unsigned int id,
		      unsigned int framerate,
		      snd_pcm_format_t fmt,
		      unsigned int channels);
void ad1843_shutdown_dac(struct snd_ad1843 *ad1843,
			 unsigned int id);
void ad1843_setup_adc(struct snd_ad1843 *ad1843,
		      unsigned int framerate,
		      snd_pcm_format_t fmt,
		      unsigned int channels);
void ad1843_shutdown_adc(struct snd_ad1843 *ad1843);
int ad1843_init(struct snd_ad1843 *ad1843);

#endif /* __SOUND_AD1843_H */
