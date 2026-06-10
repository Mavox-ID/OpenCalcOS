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
#include <beep/platform_device.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <asm/io.h>

#define IPSEL 0xFE400034

static struct snd_soc_dai_link sh7760_ac97_dai = {
	.name = "AC97",
	.stream_name = "AC97 HiFi",
	.cpu_dai_name = "hac-dai.0",	/* HAC0 */
	.codec_dai_name = "ac97-hifi",
	.platform_name = "sh7760-pcm-audio",
	.codec_name = "ac97-codec",
	.ops = NULL,
};

static struct snd_soc_card sh7760_ac97_soc_machine  = {
	.name = "SH7760 AC97",
	.owner = THIS_MODULE,
	.dai_link = &sh7760_ac97_dai,
	.num_links = 1,
};

static struct platform_device *sh7760_ac97_snd_device;

static int __init sh7760_ac97_init(void)
{
	int ret;
	unsigned short ipsel;

	/* enable both AC97 controllers in pinmux reg */
	ipsel = __raw_readw(IPSEL);
	__raw_writew(ipsel | (3 << 10), IPSEL);

	ret = -ENOMEM;
	sh7760_ac97_snd_device = platform_device_alloc("soc-audio", -1);
	if (!sh7760_ac97_snd_device)
		goto out;

	platform_set_drvdata(sh7760_ac97_snd_device,
			     &sh7760_ac97_soc_machine);
	ret = platform_device_add(sh7760_ac97_snd_device);

	if (ret)
		platform_device_put(sh7760_ac97_snd_device);

out:
	return ret;
}

static void __exit sh7760_ac97_exit(void)
{
	platform_device_unregister(sh7760_ac97_snd_device);
}

module_init(sh7760_ac97_init);
module_exit(sh7760_ac97_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Generic SH7760 AC97 sound machine");
MODULE_AUTHOR("Manuel Lauss <mano@roarinelk.homebeep.net>");
