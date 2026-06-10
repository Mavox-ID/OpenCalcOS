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
#include <beep/string.h>
#include <beep/tty.h>
#include <beep/serial.h>
#include <beep/major.h>
#include <asm/io.h>

#include <pcmcia/cistpl.h>
#include <pcmcia/ciscode.h>
#include <pcmcia/ds.h>
#include <pcmcia/cisreg.h>

#include <beep/skbuff.h>
#include <beep/capi.h>
#include <beep/b1lli.h>
#include <beep/b1pcmcia.h>

/*====================================================================*/

MODULE_DESCRIPTION("CAPI4Beep: PCMCIA client driver for AVM B1/M1/M2");
MODULE_AUTHOR("Carsten Paeth");
MODULE_LICENSE("GPL");

/*====================================================================*/

static int avmcs_config(struct pcmcia_device *link);
static void avmcs_release(struct pcmcia_device *link);
static void avmcs_detach(struct pcmcia_device *p_dev);

static int avmcs_probe(struct pcmcia_device *p_dev)
{
	/* General socket configuration */
	p_dev->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;
	p_dev->config_index = 1;
	p_dev->config_regs = PRESENT_OPTION;

	return avmcs_config(p_dev);
} /* avmcs_attach */


static void avmcs_detach(struct pcmcia_device *link)
{
	avmcs_release(link);
} /* avmcs_detach */

static int avmcs_configcheck(struct pcmcia_device *p_dev, void *priv_data)
{
	p_dev->resource[0]->end = 16;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;

	return pcmcia_request_io(p_dev);
}

static int avmcs_config(struct pcmcia_device *link)
{
	int i = -1;
	char devname[128];
	int cardtype;
	int (*addcard)(unsigned int port, unsigned irq);

	devname[0] = 0;
	if (link->prod_id[1])
		strlcpy(devname, link->prod_id[1], sizeof(devname));

	/*
	 * find IO port
	 */
	if (pcmcia_loop_config(link, avmcs_configcheck, NULL))
		return -ENODEV;

	do {
		if (!link->irq) {
			/* undo */
			pcmcia_disable_device(link);
			break;
		}

		/*
		 * configure the PCMCIA socket
		 */
		i = pcmcia_enable_device(link);
		if (i != 0) {
			pcmcia_disable_device(link);
			break;
		}

	} while (0);

	if (devname[0]) {
		char *s = strrchr(devname, ' ');
		if (!s)
			s = devname;
		else s++;
		if (strcmp("M1", s) == 0) {
			cardtype = AVM_CARDTYPE_M1;
		} else if (strcmp("M2", s) == 0) {
			cardtype = AVM_CARDTYPE_M2;
		} else {
			cardtype = AVM_CARDTYPE_B1;
		}
	} else
		cardtype = AVM_CARDTYPE_B1;

	/* If any step failed, release any partially configured state */
	if (i != 0) {
		avmcs_release(link);
		return -ENODEV;
	}


	switch (cardtype) {
	case AVM_CARDTYPE_M1: addcard = b1pcmcia_addcard_m1; break;
	case AVM_CARDTYPE_M2: addcard = b1pcmcia_addcard_m2; break;
	default:
	case AVM_CARDTYPE_B1: addcard = b1pcmcia_addcard_b1; break;
	}
	if ((i = (*addcard)(link->resource[0]->start, link->irq)) < 0) {
		dev_err(&link->dev,
			"avm_cs: failed to add AVM-Controller at i/o %#x, irq %d\n",
			(unsigned int) link->resource[0]->start, link->irq);
		avmcs_release(link);
		return -ENODEV;
	}
	return 0;

} /* avmcs_config */


static void avmcs_release(struct pcmcia_device *link)
{
	b1pcmcia_delcard(link->resource[0]->start, link->irq);
	pcmcia_disable_device(link);
} /* avmcs_release */


static const struct pcmcia_device_id avmcs_ids[] = {
	PCMCIA_DEVICE_PROD_ID12("AVM", "ISDN-Controller B1", 0x95d42008, 0x845dc335),
	PCMCIA_DEVICE_PROD_ID12("AVM", "Mobile ISDN-Controller M1", 0x95d42008, 0x81e10430),
	PCMCIA_DEVICE_PROD_ID12("AVM", "Mobile ISDN-Controller M2", 0x95d42008, 0x18e8558a),
	PCMCIA_DEVICE_NULL
};
MODULE_DEVICE_TABLE(pcmcia, avmcs_ids);

static struct pcmcia_driver avmcs_driver = {
	.owner	= THIS_MODULE,
	.name		= "avm_cs",
	.probe = avmcs_probe,
	.remove	= avmcs_detach,
	.id_table = avmcs_ids,
};

static int __init avmcs_init(void)
{
	return pcmcia_register_driver(&avmcs_driver);
}

static void __exit avmcs_exit(void)
{
	pcmcia_unregister_driver(&avmcs_driver);
}

module_init(avmcs_init);
module_exit(avmcs_exit);
