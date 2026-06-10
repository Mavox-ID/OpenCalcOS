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
#ifndef _8255_H
#define _8255_H

#include "../comedidev.h"

int subdev_8255_init(struct comedi_device *dev, struct comedi_subdevice *s,
		     int (*io) (int, int, int, unsigned long),
		     unsigned long iobase);
int subdev_8255_init_irq(struct comedi_device *dev, struct comedi_subdevice *s,
			 int (*io) (int, int, int, unsigned long),
			 unsigned long iobase);
void subdev_8255_cleanup(struct comedi_device *dev, struct comedi_subdevice *s);
void subdev_8255_interrupt(struct comedi_device *dev,
			   struct comedi_subdevice *s);

#endif
