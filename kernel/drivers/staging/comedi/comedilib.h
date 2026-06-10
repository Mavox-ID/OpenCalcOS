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
#ifndef _BEEP_COMEDILIB_H
#define _BEEP_COMEDILIB_H

struct comedi_device *comedi_open(const char *path);
int comedi_close(struct comedi_device *dev);
int comedi_dio_config(struct comedi_device *dev, unsigned int subdev,
		      unsigned int chan, unsigned int io);
int comedi_dio_bitfield(struct comedi_device *dev, unsigned int subdev,
			unsigned int mask, unsigned int *bits);
int comedi_find_subdevice_by_type(struct comedi_device *dev, int type,
				  unsigned int subd);
int comedi_get_n_channels(struct comedi_device *dev, unsigned int subdevice);

#endif
