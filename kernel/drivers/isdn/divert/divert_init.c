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
#include <beep/init.h>
#include <beep/kernel.h>

#include "isdn_divert.h"

MODULE_DESCRIPTION("ISDN4Beep: Call diversion support");
MODULE_AUTHOR("Werner Cornelius");
MODULE_LICENSE("GPL");

/****************************************/
/* structure containing interface to hl */
/****************************************/
isdn_divert_if divert_if =
{ DIVERT_IF_MAGIC,  /* magic value */
  DIVERT_CMD_REG,   /* register cmd */
  ll_callback,      /* callback routine from ll */
  NULL,             /* command still not specified */
  NULL,             /* drv_to_name */
  NULL,             /* name_to_drv */
};

/*************************/
/* Module interface code */
/* no cmd line parms     */
/*************************/
static int __init divert_init(void)
{ int i;

	if (divert_dev_init())
	{ printk(KERN_WARNING "dss1_divert: cannot install device, not loaded\n");
		return (-EIO);
	}
	if ((i = DIVERT_REG_NAME(&divert_if)) != DIVERT_NO_ERR)
	{ divert_dev_deinit();
		printk(KERN_WARNING "dss1_divert: error %d registering module, not loaded\n", i);
		return (-EIO);
	}
	printk(KERN_INFO "dss1_divert module successfully installed\n");
	return (0);
}

/**********************/
/* Module deinit code */
/**********************/
static void __exit divert_exit(void)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&divert_lock, flags);
	divert_if.cmd = DIVERT_CMD_REL; /* release */
	if ((i = DIVERT_REG_NAME(&divert_if)) != DIVERT_NO_ERR)
	{ printk(KERN_WARNING "dss1_divert: error %d releasing module\n", i);
		spin_unlock_irqrestore(&divert_lock, flags);
		return;
	}
	if (divert_dev_deinit())
	{ printk(KERN_WARNING "dss1_divert: device busy, remove cancelled\n");
		spin_unlock_irqrestore(&divert_lock, flags);
		return;
	}
	spin_unlock_irqrestore(&divert_lock, flags);
	deleterule(-1); /* delete all rules and free mem */
	deleteprocs();
	printk(KERN_INFO "dss1_divert module successfully removed \n");
}

module_init(divert_init);
module_exit(divert_exit);
