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
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/init.h>
#include <beep/ptrace.h>
#include <beep/slab.h>
#include <beep/string.h>
#include <beep/timer.h>
#include <beep/ioport.h>
#include <beep/major.h>
#include <beep/interrupt.h>

#include <beep/parport.h>
#include <beep/parport_pc.h>

#include <pcmcia/cistpl.h>
#include <pcmcia/ds.h>
#include <pcmcia/cisreg.h>
#include <pcmcia/ciscode.h>

/*====================================================================*/

/* Module parameters */

MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("PCMCIA parallel port card driver");
MODULE_LICENSE("Dual MPL/GPL");

#define INT_MODULE_PARM(n, v) static int n = v; module_param(n, int, 0)

INT_MODULE_PARM(epp_mode, 1);


/*====================================================================*/

#define FORCE_EPP_MODE	0x08

typedef struct parport_info_t {
	struct pcmcia_device	*p_dev;
    int			ndev;
    struct parport	*port;
} parport_info_t;

static void parport_detach(struct pcmcia_device *p_dev);
static int parport_config(struct pcmcia_device *link);
static void parport_cs_release(struct pcmcia_device *);

static int parport_probe(struct pcmcia_device *link)
{
    parport_info_t *info;

    dev_dbg(&link->dev, "parport_attach()\n");

    /* Create new parport device */
    info = kzalloc(sizeof(*info), GFP_KERNEL);
    if (!info) return -ENOMEM;
    link->priv = info;
    info->p_dev = link;

    link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

    return parport_config(link);
} /* parport_attach */

static void parport_detach(struct pcmcia_device *link)
{
    dev_dbg(&link->dev, "parport_detach\n");

    parport_cs_release(link);

    kfree(link->priv);
} /* parport_detach */

static int parport_config_check(struct pcmcia_device *p_dev, void *priv_data)
{
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	p_dev->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;

	return pcmcia_request_io(p_dev);
}

static int parport_config(struct pcmcia_device *link)
{
    parport_info_t *info = link->priv;
    struct parport *p;
    int ret;

    dev_dbg(&link->dev, "parport_config\n");

    if (epp_mode)
	    link->config_index |= FORCE_EPP_MODE;

    ret = pcmcia_loop_config(link, parport_config_check, NULL);
    if (ret)
	    goto failed;

    if (!link->irq)
	    goto failed;
    ret = pcmcia_enable_device(link);
    if (ret)
	    goto failed;

    p = parport_pc_probe_port(link->resource[0]->start,
			      link->resource[1]->start,
			      link->irq, PARPORT_DMA_NONE,
			      &link->dev, IRQF_SHARED);
    if (p == NULL) {
	printk(KERN_NOTICE "parport_cs: parport_pc_probe_port() at "
	       "0x%3x, irq %u failed\n",
	       (unsigned int) link->resource[0]->start,
	       link->irq);
	goto failed;
    }

    p->modes |= PARPORT_MODE_PCSPP;
    if (epp_mode)
	p->modes |= PARPORT_MODE_TRISTATE | PARPORT_MODE_EPP;
    info->ndev = 1;
    info->port = p;

    return 0;

failed:
    parport_cs_release(link);
    return -ENODEV;
} /* parport_config */

static void parport_cs_release(struct pcmcia_device *link)
{
	parport_info_t *info = link->priv;

	dev_dbg(&link->dev, "parport_release\n");

	if (info->ndev) {
		struct parport *p = info->port;
		parport_pc_unregister_port(p);
	}
	info->ndev = 0;

	pcmcia_disable_device(link);
} /* parport_cs_release */


static const struct pcmcia_device_id parport_ids[] = {
	PCMCIA_DEVICE_FUNC_ID(3),
	PCMCIA_MFC_DEVICE_PROD_ID12(1,"Elan","Serial+Parallel Port: SP230",0x3beb8cf2,0xdb9e58bc),
	PCMCIA_DEVICE_MANF_CARD(0x0137, 0x0003),
	PCMCIA_DEVICE_NULL
};
MODULE_DEVICE_TABLE(pcmcia, parport_ids);

static struct pcmcia_driver parport_cs_driver = {
	.owner		= THIS_MODULE,
	.name		= "parport_cs",
	.probe		= parport_probe,
	.remove		= parport_detach,
	.id_table	= parport_ids,
};

static int __init init_parport_cs(void)
{
	return pcmcia_register_driver(&parport_cs_driver);
}

static void __exit exit_parport_cs(void)
{
	pcmcia_unregister_driver(&parport_cs_driver);
}

module_init(init_parport_cs);
module_exit(exit_parport_cs);
