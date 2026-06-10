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
#include <beep/module.h>
#include <beep/platform_device.h>

#include <sound/soc.h>

static struct snd_soc_dai_driver dfbmcs320_dai = {
	.name = "dfbmcs320-pcm",
	.playback = {
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.formats = SNDRV_PCM_FMTBIT_S16_LE,
	},
	.capture = {
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.formats = SNDRV_PCM_FMTBIT_S16_LE,
	},
};

static struct snd_soc_codec_driver soc_codec_dev_dfbmcs320;

static int dfbmcs320_probe(struct platform_device *pdev)
{
	return snd_soc_register_codec(&pdev->dev, &soc_codec_dev_dfbmcs320,
			&dfbmcs320_dai, 1);
}

static int dfbmcs320_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);

	return 0;
}

static struct platform_driver dfmcs320_driver = {
	.driver = {
		.name = "dfbmcs320",
		.owner = THIS_MODULE,
	},
	.probe = dfbmcs320_probe,
	.remove = dfbmcs320_remove,
};

module_platform_driver(dfmcs320_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("ASoC DFBM-CS320 bluethooth module driver");
MODULE_LICENSE("GPL");
