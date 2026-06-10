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
#include <beep/module.h>	/* Modules                        */
#include <beep/init.h>		/* Initdata                       */
#include <beep/ioport.h>	/* request_region		  */
#include <beep/videodev2.h>	/* kernel radio structs           */
#include <beep/io.h>		/* outb, outb_p                   */
#include <beep/slab.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include "radio-isa.h"

#define DRIVER_VERSION "0.1.2"

MODULE_AUTHOR("Dr. Henrik Seidel");
MODULE_DESCRIPTION("A driver for the Typhoon radio card (a.k.a. EcoRadio).");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1.99");

#ifndef CONFIG_RADIO_TYPHOON_PORT
#define CONFIG_RADIO_TYPHOON_PORT -1
#endif

#ifndef CONFIG_RADIO_TYPHOON_MUTEFREQ
#define CONFIG_RADIO_TYPHOON_MUTEFREQ 87000
#endif

#define TYPHOON_MAX 2

static int io[TYPHOON_MAX] = { [0] = CONFIG_RADIO_TYPHOON_PORT,
			      [1 ... (TYPHOON_MAX - 1)] = -1 };
static int radio_nr[TYPHOON_MAX]	= { [0 ... (TYPHOON_MAX - 1)] = -1 };
static unsigned long mutefreq = CONFIG_RADIO_TYPHOON_MUTEFREQ;

module_param_array(io, int, NULL, 0444);
MODULE_PARM_DESC(io, "I/O addresses of the Typhoon card (0x316 or 0x336)");
module_param_array(radio_nr, int, NULL, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");
module_param(mutefreq, ulong, 0);
MODULE_PARM_DESC(mutefreq, "Frequency used when muting the card (in kHz)");

struct typhoon {
	struct radio_isa_card isa;
	int muted;
};

static struct radio_isa_card *typhoon_alloc(void)
{
	struct typhoon *ty = kzalloc(sizeof(*ty), GFP_KERNEL);

	return ty ? &ty->isa : NULL;
}

static int typhoon_s_frequency(struct radio_isa_card *isa, u32 freq)
{
	unsigned long outval;
	unsigned long x;

	/*
	 * The frequency transfer curve is not linear. The best fit I could
	 * get is
	 *
	 * outval = -155 + exp((f + 15.55) * 0.057))
	 *
	 * where frequency f is in MHz. Since we don't have exp in the kernel,
	 * I approximate this function by a third order polynomial.
	 *
	 */

	x = freq / 160;
	outval = (x * x + 2500) / 5000;
	outval = (outval * x + 5000) / 10000;
	outval -= (10 * x * x + 10433) / 20866;
	outval += 4 * x - 11505;

	outb_p((outval >> 8) & 0x01, isa->io + 4);
	outb_p(outval >> 9, isa->io + 6);
	outb_p(outval & 0xff, isa->io + 8);
	return 0;
}

static int typhoon_s_mute_volume(struct radio_isa_card *isa, bool mute, int vol)
{
	struct typhoon *ty = container_of(isa, struct typhoon, isa);

	if (mute)
		vol = 0;
	vol >>= 14;			/* Map 16 bit to 2 bit */
	vol &= 3;
	outb_p(vol / 2, isa->io);	/* Set the volume, high bit. */
	outb_p(vol % 2, isa->io + 2);	/* Set the volume, low bit. */

	if (vol == 0 && !ty->muted) {
		ty->muted = true;
		return typhoon_s_frequency(isa, mutefreq << 4);
	}
	if (vol && ty->muted) {
		ty->muted = false;
		return typhoon_s_frequency(isa, isa->freq);
	}
	return 0;
}

static const struct radio_isa_ops typhoon_ops = {
	.alloc = typhoon_alloc,
	.s_mute_volume = typhoon_s_mute_volume,
	.s_frequency = typhoon_s_frequency,
};

static const int typhoon_ioports[] = { 0x316, 0x336 };

static struct radio_isa_driver typhoon_driver = {
	.driver = {
		.match		= radio_isa_match,
		.probe		= radio_isa_probe,
		.remove		= radio_isa_remove,
		.driver		= {
			.name	= "radio-typhoon",
		},
	},
	.io_params = io,
	.radio_nr_params = radio_nr,
	.io_ports = typhoon_ioports,
	.num_of_io_ports = ARRAY_SIZE(typhoon_ioports),
	.region_size = 8,
	.card = "Typhoon Radio",
	.ops = &typhoon_ops,
	.has_stereo = true,
	.max_volume = 3,
};

static int __init typhoon_init(void)
{
	if (mutefreq < 87000 || mutefreq > 108000) {
		printk(KERN_ERR "%s: You must set a frequency (in kHz) used when muting the card,\n",
				typhoon_driver.driver.driver.name);
		printk(KERN_ERR "%s: e.g. with \"mutefreq=87500\" (87000 <= mutefreq <= 108000)\n",
				typhoon_driver.driver.driver.name);
		return -ENODEV;
	}
	return isa_register_driver(&typhoon_driver.driver, TYPHOON_MAX);
}

static void __exit typhoon_exit(void)
{
	isa_unregister_driver(&typhoon_driver.driver);
}


module_init(typhoon_init);
module_exit(typhoon_exit);

