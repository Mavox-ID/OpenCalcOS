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
#ifndef __SIMPLE_CARD_H
#define __SIMPLE_CARD_H

#include <sound/soc.h>

struct asoc_simple_dai_init_info {
	unsigned int fmt;
	unsigned int cpu_daifmt;
	unsigned int codec_daifmt;
	unsigned int sysclk;
};

struct asoc_simple_card_info {
	const char *name;
	const char *card;
	const char *cpu_dai;
	const char *codec;
	const char *platform;
	const char *codec_dai;
	struct asoc_simple_dai_init_info *init; /* for snd_link.init */

	/* used in simple-card.c */
	struct snd_soc_dai_link snd_link;
	struct snd_soc_card snd_card;
};

#endif /* __SIMPLE_CARD_H */
