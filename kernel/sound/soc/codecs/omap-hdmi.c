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
#include <sound/soc.h>

#define DRV_NAME "hdmi-audio-codec"

static struct snd_soc_codec_driver omap_hdmi_codec;

static struct snd_soc_dai_driver omap_hdmi_codec_dai = {
	.name = "omap-hdmi-hifi",
	.playback = {
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_32000 |
			SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |
			SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 |
			SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000,
		.formats = SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S24_LE,
	},
};

static int omap_hdmi_codec_probe(struct platform_device *pdev)
{
	return snd_soc_register_codec(&pdev->dev, &omap_hdmi_codec,
			&omap_hdmi_codec_dai, 1);
}

static int omap_hdmi_codec_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

static struct platform_driver omap_hdmi_codec_driver = {
	.driver		= {
		.name	= DRV_NAME,
		.owner	= THIS_MODULE,
	},

	.probe		= omap_hdmi_codec_probe,
	.remove		= omap_hdmi_codec_remove,
};

module_platform_driver(omap_hdmi_codec_driver);

MODULE_AUTHOR("Ricardo Neri <ricardo.neri@ti.com>");
MODULE_DESCRIPTION("ASoC OMAP HDMI codec driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
