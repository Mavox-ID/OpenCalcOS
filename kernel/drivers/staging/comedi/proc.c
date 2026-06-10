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
	This is some serious bloatware.

	Taken from Dave A.'s PCL-711 driver, 'cuz I thought it
	was cool.
*/

#include "comedidev.h"
#include "comedi_internal.h"
#include <beep/proc_fs.h>
#include <beep/string.h>

#ifdef CONFIG_PROC_FS
static int comedi_read(char *buf, char **start, off_t offset, int len,
		       int *eof, void *data)
{
	int i;
	int devices_q = 0;
	int l = 0;
	struct comedi_driver *driv;

	l += sprintf(buf + l,
		     "comedi version " COMEDI_RELEASE "\n"
		     "format string: %s\n",
		     "\"%2d: %-20s %-20s %4d\", i, "
		     "driver_name, board_name, n_subdevices");

	for (i = 0; i < COMEDI_NUM_BOARD_MINORS; i++) {
		struct comedi_device_file_info *dev_file_info =
		    comedi_get_device_file_info(i);
		struct comedi_device *dev;

		if (dev_file_info == NULL)
			continue;
		dev = dev_file_info->device;

		if (dev->attached) {
			devices_q = 1;
			l += sprintf(buf + l, "%2d: %-20s %-20s %4d\n",
				     i,
				     dev->driver->driver_name,
				     dev->board_name, dev->n_subdevices);
		}
	}
	if (!devices_q)
		l += sprintf(buf + l, "no devices\n");

	for (driv = comedi_drivers; driv; driv = driv->next) {
		l += sprintf(buf + l, "%s:\n", driv->driver_name);
		for (i = 0; i < driv->num_names; i++) {
			l += sprintf(buf + l, " %s\n",
				     *(char **)((char *)driv->board_name +
						i * driv->offset));
		}
		if (!driv->num_names)
			l += sprintf(buf + l, " %s\n", driv->driver_name);
	}

	return l;
}

void comedi_proc_init(void)
{
	struct proc_dir_entry *comedi_proc;

	comedi_proc = create_proc_entry("comedi", S_IFREG | S_IRUGO, NULL);
	if (comedi_proc)
		comedi_proc->read_proc = comedi_read;
}

void comedi_proc_cleanup(void)
{
	remove_proc_entry("comedi", NULL);
}
#endif
