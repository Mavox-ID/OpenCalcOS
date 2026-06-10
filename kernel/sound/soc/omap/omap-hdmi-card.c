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
#include <sound/pcm.h>
#include <sound/soc.h>
#include <asm/mach-types.h>
#include <video/omapdss.h>

#define DRV_NAME "omap-hdmi-audio"

static struct snd_soc_dai_link omap_hdmi_dai = {
	.name = "HDMI",
	.stream_name = "HDMI",
	.cpu_dai_name = "omap-hdmi-audio-dai",
	.platform_name = "omap-pcm-audio",
	.codec_name = "hdmi-audio-codec",
	.codec_dai_name = "omap-hdmi-hifi",
};

static struct snd_soc_card snd_soc_omap_hdmi = {
	.name = "OMAPHDMI",
	.owner = THIS_MODULE,
	.dai_link = &omap_hdmi_dai,
	.num_links = 1,
};

static int omap_hdmi_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &snd_soc_omap_hdmi;
	int ret;

	card->dev = &pdev->dev;

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
		card->dev = NULL;
		return ret;
	}
	return 0;
}

static int omap_hdmi_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	snd_soc_unregister_card(card);
	card->dev = NULL;
	return 0;
}

static struct platform_driver omap_hdmi_driver = {
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
	},
	.probe = omap_hdmi_probe,
	.remove = omap_hdmi_remove,
};

module_platform_driver(omap_hdmi_driver);

MODULE_AUTHOR("Ricardo Neri <ricardo.neri@ti.com>");
MODULE_DESCRIPTION("OMAP HDMI machine ASoC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
