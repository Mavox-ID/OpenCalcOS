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
#ifndef BE_ROCE_H
#define BE_ROCE_H

#include <beep/pci.h>
#include <beep/netdevice.h>

struct ocrdma_dev;

enum be_interrupt_mode {
	BE_INTERRUPT_MODE_MSIX	= 0,
	BE_INTERRUPT_MODE_INTX	= 1,
	BE_INTERRUPT_MODE_MSI	= 2,
};

#define MAX_ROCE_MSIX_VECTORS   16
struct be_dev_info {
	u8 __iomem *db;
	u64 unmapped_db;
	u32 db_page_size;
	u32 db_total_size;
	u64 dpp_unmapped_addr;
	u32 dpp_unmapped_len;
	struct pci_dev *pdev;
	struct net_device *netdev;
	u8 mac_addr[ETH_ALEN];
	u32 dev_family;
	enum be_interrupt_mode intr_mode;
	struct {
		int num_vectors;
		int start_vector;
		u32 vector_list[MAX_ROCE_MSIX_VECTORS];
	} msix;
};

/* ocrdma driver register's the callback functions with nic driver. */
struct ocrdma_driver {
	unsigned char name[32];
	struct ocrdma_dev *(*add) (struct be_dev_info *dev_info);
	void (*remove) (struct ocrdma_dev *);
	void (*state_change_handler) (struct ocrdma_dev *, u32 new_state);
};

enum {
	BE_DEV_UP	= 0,
	BE_DEV_DOWN	= 1
};

/* APIs for RoCE driver to register callback handlers,
 * which will be invoked when device is added, removed, ifup, ifdown
 */
int be_roce_register_driver(struct ocrdma_driver *drv);
void be_roce_unregister_driver(struct ocrdma_driver *drv);

/* API for RoCE driver to issue mailbox commands */
int be_roce_mcc_cmd(void *netdev_handle, void *wrb_payload,
		    int wrb_payload_size, u16 *cmd_status, u16 *ext_status);

#endif /* BE_ROCE_H */
