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
#include <beep/delay.h>	/* udelay, msleep                 */
#include <beep/videodev2.h>	/* kernel radio structs           */
#include <beep/mutex.h>
#include <beep/io.h>		/* outb, outb_p                   */
#include <beep/slab.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include "radio-isa.h"

MODULE_AUTHOR("C. van Schaik");
MODULE_DESCRIPTION("A driver for the Zoltrix Radio Plus.");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1.99");

#ifndef CONFIG_RADIO_ZOLTRIX_PORT
#define CONFIG_RADIO_ZOLTRIX_PORT -1
#endif

#define ZOLTRIX_MAX 2

static int io[ZOLTRIX_MAX] = { [0] = CONFIG_RADIO_ZOLTRIX_PORT,
			       [1 ... (ZOLTRIX_MAX - 1)] = -1 };
static int radio_nr[ZOLTRIX_MAX] = { [0 ... (ZOLTRIX_MAX - 1)] = -1 };

module_param_array(io, int, NULL, 0444);
MODULE_PARM_DESC(io, "I/O addresses of the Zoltrix Radio Plus card (0x20c or 0x30c)");
module_param_array(radio_nr, int, NULL, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");

struct zoltrix {
	struct radio_isa_card isa;
	int curvol;
	bool muted;
};

static struct radio_isa_card *zoltrix_alloc(void)
{
	struct zoltrix *zol = kzalloc(sizeof(*zol), GFP_KERNEL);

	return zol ? &zol->isa : NULL;
}

static int zoltrix_s_mute_volume(struct radio_isa_card *isa, bool mute, int vol)
{
	struct zoltrix *zol = container_of(isa, struct zoltrix, isa);

	zol->curvol = vol;
	zol->muted = mute;
	if (mute || vol == 0) {
		outb(0, isa->io);
		outb(0, isa->io);
		inb(isa->io + 3);            /* Zoltrix needs to be read to confirm */
		return 0;
	}

	outb(vol - 1, isa->io);
	msleep(10);
	inb(isa->io + 2);
	return 0;
}

/* tunes the radio to the desired frequency */
static int zoltrix_s_frequency(struct radio_isa_card *isa, u32 freq)
{
	struct zoltrix *zol = container_of(isa, struct zoltrix, isa);
	struct v4l2_device *v4l2_dev = &isa->v4l2_dev;
	unsigned long long bitmask, f, m;
	bool stereo = isa->stereo;
	int i;

	if (freq == 0) {
		v4l2_warn(v4l2_dev, "cannot set a frequency of 0.\n");
		return -EINVAL;
	}

	m = (freq / 160 - 8800) * 2;
	f = (unsigned long long)m + 0x4d1c;

	bitmask = 0xc480402c10080000ull;
	i = 45;

	outb(0, isa->io);
	outb(0, isa->io);
	inb(isa->io + 3);            /* Zoltrix needs to be read to confirm */

	outb(0x40, isa->io);
	outb(0xc0, isa->io);

	bitmask = (bitmask ^ ((f & 0xff) << 47) ^ ((f & 0xff00) << 30) ^ (stereo << 31));
	while (i--) {
		if ((bitmask & 0x8000000000000000ull) != 0) {
			outb(0x80, isa->io);
			udelay(50);
			outb(0x00, isa->io);
			udelay(50);
			outb(0x80, isa->io);
			udelay(50);
		} else {
			outb(0xc0, isa->io);
			udelay(50);
			outb(0x40, isa->io);
			udelay(50);
			outb(0xc0, isa->io);
			udelay(50);
		}
		bitmask *= 2;
	}
	/* termination sequence */
	outb(0x80, isa->io);
	outb(0xc0, isa->io);
	outb(0x40, isa->io);
	udelay(1000);
	inb(isa->io + 2);
	udelay(1000);

	return zoltrix_s_mute_volume(isa, zol->muted, zol->curvol);
}

/* Get signal strength */
static u32 zoltrix_g_rxsubchans(struct radio_isa_card *isa)
{
	struct zoltrix *zol = container_of(isa, struct zoltrix, isa);
	int a, b;

	outb(0x00, isa->io);         /* This stuff I found to do nothing */
	outb(zol->curvol, isa->io);
	msleep(20);

	a = inb(isa->io);
	msleep(10);
	b = inb(isa->io);

	return (a == b && a == 0xcf) ?
		V4L2_TUNER_SUB_STEREO : V4L2_TUNER_SUB_MONO;
}

static u32 zoltrix_g_signal(struct radio_isa_card *isa)
{
	struct zoltrix *zol = container_of(isa, struct zoltrix, isa);
	int a, b;

	outb(0x00, isa->io);         /* This stuff I found to do nothing */
	outb(zol->curvol, isa->io);
	msleep(20);

	a = inb(isa->io);
	msleep(10);
	b = inb(isa->io);

	if (a != b)
		return 0;

	/* I found this out by playing with a binary scanner on the card io */
	return (a == 0xcf || a == 0xdf || a == 0xef) ? 0xffff : 0;
}

static int zoltrix_s_stereo(struct radio_isa_card *isa, bool stereo)
{
	return zoltrix_s_frequency(isa, isa->freq);
}

static const struct radio_isa_ops zoltrix_ops = {
	.alloc = zoltrix_alloc,
	.s_mute_volume = zoltrix_s_mute_volume,
	.s_frequency = zoltrix_s_frequency,
	.s_stereo = zoltrix_s_stereo,
	.g_rxsubchans = zoltrix_g_rxsubchans,
	.g_signal = zoltrix_g_signal,
};

static const int zoltrix_ioports[] = { 0x20c, 0x30c };

static struct radio_isa_driver zoltrix_driver = {
	.driver = {
		.match		= radio_isa_match,
		.probe		= radio_isa_probe,
		.remove		= radio_isa_remove,
		.driver		= {
			.name	= "radio-zoltrix",
		},
	},
	.io_params = io,
	.radio_nr_params = radio_nr,
	.io_ports = zoltrix_ioports,
	.num_of_io_ports = ARRAY_SIZE(zoltrix_ioports),
	.region_size = 2,
	.card = "Zoltrix Radio Plus",
	.ops = &zoltrix_ops,
	.has_stereo = true,
	.max_volume = 15,
};

static int __init zoltrix_init(void)
{
	return isa_register_driver(&zoltrix_driver.driver, ZOLTRIX_MAX);
}

static void __exit zoltrix_exit(void)
{
	isa_unregister_driver(&zoltrix_driver.driver);
}

module_init(zoltrix_init);
module_exit(zoltrix_exit);

