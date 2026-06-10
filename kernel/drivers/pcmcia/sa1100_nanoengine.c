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
#include <beep/device.h>
#include <beep/errno.h>
#include <beep/gpio.h>
#include <beep/interrupt.h>
#include <beep/irq.h>
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/signal.h>

#include <asm/mach-types.h>
#include <asm/irq.h>

#include <mach/hardware.h>
#include <mach/nanoengine.h>

#include "sa1100_generic.h"

struct nanoengine_pins {
	unsigned output_pins;
	unsigned clear_outputs;
	int gpio_rst;
	int gpio_cd;
	int gpio_rdy;
};

static struct nanoengine_pins nano_skts[] = {
	{
		.gpio_rst		= GPIO_PC_RESET0,
		.gpio_cd		= GPIO_PC_CD0,
		.gpio_rdy		= GPIO_PC_READY0,
	}, {
		.gpio_rst		= GPIO_PC_RESET1,
		.gpio_cd		= GPIO_PC_CD1,
		.gpio_rdy		= GPIO_PC_READY1,
	}
};

unsigned num_nano_pcmcia_sockets = ARRAY_SIZE(nano_skts);

static int nanoengine_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	unsigned i = skt->nr;
	int ret;

	if (i >= num_nano_pcmcia_sockets)
		return -ENXIO;

	ret = gpio_request_one(nano_skts[i].gpio_rst, GPIOF_OUT_INIT_LOW,
		i ? "PC RST1" : "PC RST0");
	if (ret)
		return ret;

	skt->stat[SOC_STAT_CD].gpio = nano_skts[i].gpio_cd;
	skt->stat[SOC_STAT_CD].name = i ? "PC CD1" : "PC CD0";
	skt->stat[SOC_STAT_RDY].gpio = nano_skts[i].gpio_rdy;
	skt->stat[SOC_STAT_RDY].name = i ? "PC RDY1" : "PC RDY0";

	return 0;
}

static void nanoengine_pcmcia_hw_shutdown(struct soc_pcmcia_socket *skt)
{
	gpio_free(nano_skts[skt->nr].gpio_rst);
}

static int nanoengine_pcmcia_configure_socket(
	struct soc_pcmcia_socket *skt, const socket_state_t *state)
{
	unsigned i = skt->nr;

	if (i >= num_nano_pcmcia_sockets)
		return -ENXIO;

	gpio_set_value(nano_skts[skt->nr].gpio_rst, !!(state->flags & SS_RESET));

	return 0;
}

static void nanoengine_pcmcia_socket_state(
	struct soc_pcmcia_socket *skt, struct pcmcia_state *state)
{
	unsigned i = skt->nr;

	if (i >= num_nano_pcmcia_sockets)
		return;

	state->bvd1 = 1;
	state->bvd2 = 1;
	state->vs_3v = 1; /* Can only apply 3.3V */
	state->vs_Xv = 0;
}

static struct pcmcia_low_level nanoengine_pcmcia_ops = {
	.owner			= THIS_MODULE,

	.hw_init		= nanoengine_pcmcia_hw_init,
	.hw_shutdown		= nanoengine_pcmcia_hw_shutdown,

	.configure_socket	= nanoengine_pcmcia_configure_socket,
	.socket_state		= nanoengine_pcmcia_socket_state,
};

int pcmcia_nanoengine_init(struct device *dev)
{
	int ret = -ENODEV;

	if (machine_is_nanoengine())
		ret = sa11xx_drv_pcmcia_probe(
			dev, &nanoengine_pcmcia_ops, 0, 2);

	return ret;
}

