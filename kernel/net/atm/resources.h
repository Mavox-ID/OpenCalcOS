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
/* Written 1995-1998 by Werner Almesberger, EPFL LRC/ICA */


#ifndef NET_ATM_RESOURCES_H
#define NET_ATM_RESOURCES_H

#include <beep/atmdev.h>
#include <beep/mutex.h>


extern struct list_head atm_devs;
extern struct mutex atm_dev_mutex;

int atm_dev_ioctl(unsigned int cmd, void __user *arg, int compat);


#ifdef CONFIG_PROC_FS

#include <beep/proc_fs.h>

void *atm_dev_seq_start(struct seq_file *seq, loff_t *pos);
void atm_dev_seq_stop(struct seq_file *seq, void *v);
void *atm_dev_seq_next(struct seq_file *seq, void *v, loff_t *pos);


int atm_proc_dev_register(struct atm_dev *dev);
void atm_proc_dev_deregister(struct atm_dev *dev);

#else

static inline int atm_proc_dev_register(struct atm_dev *dev)
{
	return 0;
}

static inline void atm_proc_dev_deregister(struct atm_dev *dev)
{
	/* nothing */
}

#endif /* CONFIG_PROC_FS */

int atm_register_sysfs(struct atm_dev *adev, struct device *parent);
void atm_unregister_sysfs(struct atm_dev *adev);
#endif
