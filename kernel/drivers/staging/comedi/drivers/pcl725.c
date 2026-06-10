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
/*
Driver: pcl725
Description: Advantech PCL-725 (& compatibles)
Author: ds
Status: unknown
Devices: [Advantech] PCL-725 (pcl725)
*/

#include "../comedidev.h"

#include <beep/ioport.h>

#define PCL725_SIZE 2

#define PCL725_DO 0
#define PCL725_DI 1

static int pcl725_do_insn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	if (data[0]) {
		s->state &= ~data[0];
		s->state |= (data[0] & data[1]);
		outb(s->state, dev->iobase + PCL725_DO);
	}

	data[1] = s->state;

	return insn->n;
}

static int pcl725_di_insn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	data[1] = inb(dev->iobase + PCL725_DI);

	return insn->n;
}

static int pcl725_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	unsigned long iobase;
	int ret;

	iobase = it->options[0];
	printk(KERN_INFO "comedi%d: pcl725: 0x%04lx ", dev->minor, iobase);
	if (!request_region(iobase, PCL725_SIZE, "pcl725")) {
		printk("I/O port conflict\n");
		return -EIO;
	}
	dev->board_name = "pcl725";
	dev->iobase = iobase;
	dev->irq = 0;

	ret = comedi_alloc_subdevices(dev, 2);
	if (ret)
		return ret;

	s = &dev->subdevices[0];
	/* do */
	s->type = COMEDI_SUBD_DO;
	s->subdev_flags = SDF_WRITABLE;
	s->maxdata = 1;
	s->n_chan = 8;
	s->insn_bits = pcl725_do_insn;
	s->range_table = &range_digital;

	s = &dev->subdevices[1];
	/* di */
	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE;
	s->maxdata = 1;
	s->n_chan = 8;
	s->insn_bits = pcl725_di_insn;
	s->range_table = &range_digital;

	printk(KERN_INFO "\n");

	return 0;
}

static void pcl725_detach(struct comedi_device *dev)
{
	if (dev->iobase)
		release_region(dev->iobase, PCL725_SIZE);
}

static struct comedi_driver pcl725_driver = {
	.driver_name	= "pcl725",
	.module		= THIS_MODULE,
	.attach		= pcl725_attach,
	.detach		= pcl725_detach,
};
module_comedi_driver(pcl725_driver);

MODULE_AUTHOR("Comedi http://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
