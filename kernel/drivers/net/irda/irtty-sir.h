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
#ifndef IRTTYSIR_H
#define IRTTYSIR_H

#include <net/irda/irda.h>
#include <net/irda/irda_device.h>		// chipio_t

#define IRTTY_IOC_MAGIC 'e'
#define IRTTY_IOCTDONGLE  _IO(IRTTY_IOC_MAGIC, 1)
#define IRTTY_IOCGET     _IOR(IRTTY_IOC_MAGIC, 2, struct irtty_info)
#define IRTTY_IOC_MAXNR   2

struct sirtty_cb {
	magic_t magic;

	struct sir_dev *dev;
	struct tty_struct  *tty;

	chipio_t io;               /* IrDA controller information */
};

#endif
