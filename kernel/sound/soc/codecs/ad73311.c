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
#include <beep/init.h>
#include <beep/slab.h>
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/device.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/ac97_codec.h>
#include <sound/initval.h>
#include <sound/soc.h>

#include "ad73311.h"

static struct snd_soc_dai_driver ad73311_dai = {
	.name = "ad73311-hifi",
	.playback = {
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.formats = SNDRV_PCM_FMTBIT_S16_LE, },
	.capture = {
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.formats = SNDRV_PCM_FMTBIT_S16_LE, },
};

static struct snd_soc_codec_driver soc_codec_dev_ad73311;

static int ad73311_probe(struct platform_device *pdev)
{
	return snd_soc_register_codec(&pdev->dev,
			&soc_codec_dev_ad73311, &ad73311_dai, 1);
}

static int ad73311_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

static struct platform_driver ad73311_codec_driver = {
	.driver = {
			.name = "ad73311",
			.owner = THIS_MODULE,
	},

	.probe = ad73311_probe,
	.remove = ad73311_remove,
};

module_platform_driver(ad73311_codec_driver);

MODULE_DESCRIPTION("ASoC ad73311 driver");
MODULE_AUTHOR("Cliff Cai ");
MODULE_LICENSE("GPL");
