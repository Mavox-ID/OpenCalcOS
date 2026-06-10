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
#include <beep/timer.h>
#include <beep/interrupt.h>
#include <beep/platform_device.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <asm/mach-au1x00/au1000.h>
#include <asm/mach-db1x00/bcsr.h>

#include "psc.h"

static struct snd_soc_dai_link db1000_ac97_dai = {
	.name		= "AC97",
	.stream_name	= "AC97 HiFi",
	.codec_dai_name	= "ac97-hifi",
	.cpu_dai_name	= "alchemy-ac97c",
	.platform_name	= "alchemy-pcm-dma.0",
	.codec_name	= "ac97-codec",
};

static struct snd_soc_card db1000_ac97 = {
	.name		= "DB1000_AC97",
	.owner		= THIS_MODULE,
	.dai_link	= &db1000_ac97_dai,
	.num_links	= 1,
};

static int db1000_audio_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &db1000_ac97;
	card->dev = &pdev->dev;
	return snd_soc_register_card(card);
}

static int db1000_audio_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	snd_soc_unregister_card(card);
	return 0;
}

static struct platform_driver db1000_audio_driver = {
	.driver	= {
		.name	= "db1000-audio",
		.owner	= THIS_MODULE,
		.pm	= &snd_soc_pm_ops,
	},
	.probe		= db1000_audio_probe,
	.remove		= db1000_audio_remove,
};

module_platform_driver(db1000_audio_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DB1000/DB1500/DB1100 ASoC audio");
MODULE_AUTHOR("Manuel Lauss");
