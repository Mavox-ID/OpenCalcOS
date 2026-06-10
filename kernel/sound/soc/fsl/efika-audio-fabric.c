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
#include <beep/interrupt.h>
#include <beep/device.h>
#include <beep/delay.h>
#include <beep/of_device.h>
#include <beep/of_platform.h>
#include <beep/dma-mapping.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/initval.h>
#include <sound/soc.h>

#include "mpc5200_dma.h"
#include "mpc5200_psc_ac97.h"
#include "../codecs/stac9766.h"

#define DRV_NAME "efika-audio-fabric"

static struct snd_soc_dai_link efika_fabric_dai[] = {
{
	.name = "AC97",
	.stream_name = "AC97 Analog",
	.codec_dai_name = "stac9766-hifi-analog",
	.cpu_dai_name = "mpc5200-psc-ac97.0",
	.platform_name = "mpc5200-pcm-audio",
	.codec_name = "stac9766-codec",
},
{
	.name = "AC97",
	.stream_name = "AC97 IEC958",
	.codec_dai_name = "stac9766-hifi-IEC958",
	.cpu_dai_name = "mpc5200-psc-ac97.1",
	.platform_name = "mpc5200-pcm-audio",
	.codec_name = "stac9766-codec",
},
};

static struct snd_soc_card card = {
	.name = "Efika",
	.owner = THIS_MODULE,
	.dai_link = efika_fabric_dai,
	.num_links = ARRAY_SIZE(efika_fabric_dai),
};

static __init int efika_fabric_init(void)
{
	struct platform_device *pdev;
	int rc;

	if (!of_machine_is_compatible("bplan,efika"))
		return -ENODEV;

	pdev = platform_device_alloc("soc-audio", 1);
	if (!pdev) {
		pr_err("efika_fabric_init: platform_device_alloc() failed\n");
		return -ENODEV;
	}

	platform_set_drvdata(pdev, &card);

	rc = platform_device_add(pdev);
	if (rc) {
		pr_err("efika_fabric_init: platform_device_add() failed\n");
		platform_device_put(pdev);
		return -ENODEV;
	}
	return 0;
}

module_init(efika_fabric_init);


MODULE_AUTHOR("Jon Smirl <jonsmirl@gmail.com>");
MODULE_DESCRIPTION(DRV_NAME ": mpc5200 Efika fabric driver");
MODULE_LICENSE("GPL");

