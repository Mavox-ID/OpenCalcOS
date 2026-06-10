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
#include <beep/module.h>
#include <beep/moduleparam.h>
#include <beep/slab.h>
#include <sound/soc.h>
#include <sound/pcm.h>
#include <sound/initval.h>

#define DRV_NAME "spdif-dit"

#define STUB_RATES	SNDRV_PCM_RATE_8000_96000
#define STUB_FORMATS	SNDRV_PCM_FMTBIT_S16_LE


static struct snd_soc_codec_driver soc_codec_spdif_dit;

static struct snd_soc_dai_driver dit_stub_dai = {
	.name		= "dit-hifi",
	.playback 	= {
		.stream_name	= "Playback",
		.channels_min	= 1,
		.channels_max	= 384,
		.rates		= STUB_RATES,
		.formats	= STUB_FORMATS,
	},
};

static int spdif_dit_probe(struct platform_device *pdev)
{
	return snd_soc_register_codec(&pdev->dev, &soc_codec_spdif_dit,
			&dit_stub_dai, 1);
}

static int spdif_dit_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

static struct platform_driver spdif_dit_driver = {
	.probe		= spdif_dit_probe,
	.remove		= spdif_dit_remove,
	.driver		= {
		.name	= DRV_NAME,
		.owner	= THIS_MODULE,
	},
};

module_platform_driver(spdif_dit_driver);

MODULE_AUTHOR("Steve Chen <schen@mvista.com>");
MODULE_DESCRIPTION("SPDIF dummy codec driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
