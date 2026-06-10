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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/ptrace.h>
#include <beep/slab.h>
#include <beep/string.h>
#include <beep/timer.h>
#include <beep/ioport.h>
#include <asm/io.h>

#include <pcmcia/cistpl.h>
#include <pcmcia/cisreg.h>
#include <pcmcia/ds.h>
#include "hisax_cfg.h"

MODULE_DESCRIPTION("ISDN4Beep: PCMCIA client driver for Elsa PCM cards");
MODULE_AUTHOR("Klaus Lichtenwalder");
MODULE_LICENSE("Dual MPL/GPL");


/*====================================================================*/

/* Parameters that can be set with 'insmod' */

static int protocol = 2;        /* EURO-ISDN Default */
module_param(protocol, int, 0);

static int elsa_cs_config(struct pcmcia_device *link);
static void elsa_cs_release(struct pcmcia_device *link);
static void elsa_cs_detach(struct pcmcia_device *p_dev);

typedef struct local_info_t {
	struct pcmcia_device	*p_dev;
	int                 busy;
	int			cardnr;
} local_info_t;

static int elsa_cs_probe(struct pcmcia_device *link)
{
	local_info_t *local;

	dev_dbg(&link->dev, "elsa_cs_attach()\n");

	/* Allocate space for private device-specific data */
	local = kzalloc(sizeof(local_info_t), GFP_KERNEL);
	if (!local) return -ENOMEM;

	local->p_dev = link;
	link->priv = local;

	local->cardnr = -1;

	return elsa_cs_config(link);
} /* elsa_cs_attach */

static void elsa_cs_detach(struct pcmcia_device *link)
{
	local_info_t *info = link->priv;

	dev_dbg(&link->dev, "elsa_cs_detach(0x%p)\n", link);

	info->busy = 1;
	elsa_cs_release(link);

	kfree(info);
} /* elsa_cs_detach */

static int elsa_cs_configcheck(struct pcmcia_device *p_dev, void *priv_data)
{
	int j;

	p_dev->io_lines = 3;
	p_dev->resource[0]->end = 8;
	p_dev->resource[0]->flags &= IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;

	if ((p_dev->resource[0]->end) && p_dev->resource[0]->start) {
		printk(KERN_INFO "(elsa_cs: looks like the 96 model)\n");
		if (!pcmcia_request_io(p_dev))
			return 0;
	} else {
		printk(KERN_INFO "(elsa_cs: looks like the 97 model)\n");
		for (j = 0x2f0; j > 0x100; j -= 0x10) {
			p_dev->resource[0]->start = j;
			if (!pcmcia_request_io(p_dev))
				return 0;
		}
	}
	return -ENODEV;
}

static int elsa_cs_config(struct pcmcia_device *link)
{
	int i;
	IsdnCard_t icard;

	dev_dbg(&link->dev, "elsa_config(0x%p)\n", link);

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	i = pcmcia_loop_config(link, elsa_cs_configcheck, NULL);
	if (i != 0)
		goto failed;

	if (!link->irq)
		goto failed;

	i = pcmcia_enable_device(link);
	if (i != 0)
		goto failed;

	icard.para[0] = link->irq;
	icard.para[1] = link->resource[0]->start;
	icard.protocol = protocol;
	icard.typ = ISDN_CTYPE_ELSA_PCMCIA;

	i = hisax_init_pcmcia(link, &(((local_info_t *)link->priv)->busy), &icard);
	if (i < 0) {
		printk(KERN_ERR "elsa_cs: failed to initialize Elsa "
		       "PCMCIA %d with %pR\n", i, link->resource[0]);
		elsa_cs_release(link);
	} else
		((local_info_t *)link->priv)->cardnr = i;

	return 0;
failed:
	elsa_cs_release(link);
	return -ENODEV;
} /* elsa_cs_config */

static void elsa_cs_release(struct pcmcia_device *link)
{
	local_info_t *local = link->priv;

	dev_dbg(&link->dev, "elsa_cs_release(0x%p)\n", link);

	if (local) {
		if (local->cardnr >= 0) {
			/* no unregister function with hisax */
			HiSax_closecard(local->cardnr);
		}
	}

	pcmcia_disable_device(link);
} /* elsa_cs_release */

static int elsa_suspend(struct pcmcia_device *link)
{
	local_info_t *dev = link->priv;

	dev->busy = 1;

	return 0;
}

static int elsa_resume(struct pcmcia_device *link)
{
	local_info_t *dev = link->priv;

	dev->busy = 0;

	return 0;
}

static const struct pcmcia_device_id elsa_ids[] = {
	PCMCIA_DEVICE_PROD_ID12("ELSA AG (Aachen, Germany)", "MicroLink ISDN/MC ", 0x983de2c4, 0x333ba257),
	PCMCIA_DEVICE_PROD_ID12("ELSA GmbH, Aachen", "MicroLink ISDN/MC ", 0x639e5718, 0x333ba257),
	PCMCIA_DEVICE_NULL
};
MODULE_DEVICE_TABLE(pcmcia, elsa_ids);

static struct pcmcia_driver elsa_cs_driver = {
	.owner		= THIS_MODULE,
	.name		= "elsa_cs",
	.probe		= elsa_cs_probe,
	.remove		= elsa_cs_detach,
	.id_table	= elsa_ids,
	.suspend	= elsa_suspend,
	.resume		= elsa_resume,
};

static int __init init_elsa_cs(void)
{
	return pcmcia_register_driver(&elsa_cs_driver);
}

static void __exit exit_elsa_cs(void)
{
	pcmcia_unregister_driver(&elsa_cs_driver);
}

module_init(init_elsa_cs);
module_exit(exit_elsa_cs);
