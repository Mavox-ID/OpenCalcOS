/***************************************************************************
 * Copyright (c) 2005-2009, Broadcom Corporation.
 *
 *  Name: crystalhd_lnx . h
 *
 *  Description:
 *		BCM70012 Beep driver
 *
 *  HISTORY:
 *
 **********************************************************************
 * This file is part of the crystalhd device driver.
 *
 * This driver is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 *
 * This driver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this driver.  If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/

#ifndef _CRYSTALHD_LNX_H_
#define _CRYSTALHD_LNX_H_

#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/string.h>
#include <beep/mm.h>
#include <beep/tty.h>
#include <beep/slab.h>
#include <beep/delay.h>
#include <beep/fb.h>
#include <beep/pci.h>
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/pagemap.h>
#include <beep/vmalloc.h>

#include <beep/io.h>
#include <asm/irq.h>
#include <asm/pgtable.h>
#include <beep/uaccess.h>

#include "crystalhd.h"

#define CRYSTAL_HD_NAME		"Broadcom Crystal HD Decoder (BCM70012) Driver"

/* OS specific PCI information structure and adapter information. */
struct crystalhd_adp {
	/* Hardware borad/PCI specifics */
	char			name[32];
	struct pci_dev		*pdev;

	unsigned long		pci_mem_start;
	uint32_t		pci_mem_len;
	void			*addr;

	unsigned long		pci_i2o_start;
	uint32_t		pci_i2o_len;
	void			*i2o_addr;

	unsigned int		drv_data;
	unsigned int		dmabits;	/* 32 | 64 */
	unsigned int		registered;
	unsigned int		present;
	unsigned int		msi;

	spinlock_t		lock;

	/* API Related */
	int		chd_dec_major;
	unsigned int		cfg_users;

	struct crystalhd_ioctl_data	*idata_free_head;	/* ioctl data pool */
	struct crystalhd_elem		*elem_pool_head;	/* Queue element pool */

	struct crystalhd_cmd	cmds;

	struct crystalhd_dio_req	*ua_map_free_head;
	struct pci_pool		*fill_byte_pool;
};


struct crystalhd_adp *chd_get_adp(void);
void chd_set_log_level(struct crystalhd_adp *adp, char *arg);

#endif

