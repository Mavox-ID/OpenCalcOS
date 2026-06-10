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
#include <beep/kmemcheck.h>

#define C2PORT_NAME_LEN			32

struct device;

/*
 * C2 port basic structs
 */

/* Main struct */
struct c2port_ops;
struct c2port_device {
	kmemcheck_bitfield_begin(flags);
	unsigned int access:1;
	unsigned int flash_access:1;
	kmemcheck_bitfield_end(flags);

	int id;
	char name[C2PORT_NAME_LEN];
	struct c2port_ops *ops;
	struct mutex mutex;		/* prevent races during read/write */

	struct device *dev;

	void *private_data;
};

/* Basic operations */
struct c2port_ops {
	/* Flash layout */
	unsigned short block_size;	/* flash block size in bytes */
	unsigned short blocks_num;	/* flash blocks number */

	/* Enable or disable the access to C2 port */
	void (*access)(struct c2port_device *dev, int status);

	/* Set C2D data line as input/output */
	void (*c2d_dir)(struct c2port_device *dev, int dir);

	/* Read/write C2D data line */
	int (*c2d_get)(struct c2port_device *dev);
	void (*c2d_set)(struct c2port_device *dev, int status);

	/* Write C2CK clock line */
	void (*c2ck_set)(struct c2port_device *dev, int status);
};

/*
 * Exported functions
 */

extern struct c2port_device *c2port_device_register(char *name,
					struct c2port_ops *ops, void *devdata);
extern void c2port_device_unregister(struct c2port_device *dev);
