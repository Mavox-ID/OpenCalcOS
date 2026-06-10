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

#define STUB_RATES	SNDRV_PCM_RATE_8000_192000
#define STUB_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE)

static struct snd_soc_codec_driver soc_codec_spdif_dir;

static struct snd_soc_dai_driver dir_stub_dai = {
	.name		= "dir-hifi",
	.capture	= {
		.stream_name	= "Capture",
		.channels_min	= 1,
		.channels_max	= 384,
		.rates		= STUB_RATES,
		.formats	= STUB_FORMATS,
	},
};

static int spdif_dir_probe(struct platform_device *pdev)
{
	return snd_soc_register_codec(&pdev->dev, &soc_codec_spdif_dir,
			&dir_stub_dai, 1);
}

static int spdif_dir_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

static struct platform_driver spdif_dir_driver = {
	.probe		= spdif_dir_probe,
	.remove		= spdif_dir_remove,
	.driver		= {
		.name	= "spdif-dir",
		.owner	= THIS_MODULE,
	},
};

module_platform_driver(spdif_dir_driver);

MODULE_DESCRIPTION("ASoC SPDIF DIR driver");
MODULE_AUTHOR("Vipin Kumar <vipin.kumar@st.com>");
MODULE_LICENSE("GPL");
