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
#ifndef _WM8350_H
#define _WM8350_H

#include <sound/soc.h>
#include <beep/mfd/wm8350/audio.h>

enum wm8350_jack {
	WM8350_JDL = 1,
	WM8350_JDR = 2,
};

int wm8350_hp_jack_detect(struct snd_soc_codec *codec, enum wm8350_jack which,
			  struct snd_soc_jack *jack, int report);
int wm8350_mic_jack_detect(struct snd_soc_codec *codec,
			   struct snd_soc_jack *jack,
			   int detect_report, int short_report);

#endif
