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
#ifndef __CSIO_INIT_H__
#define __CSIO_INIT_H__

#include <beep/pci.h>
#include <beep/if_ether.h>
#include <scsi/scsi.h>
#include <scsi/scsi_device.h>
#include <scsi/scsi_host.h>
#include <scsi/scsi_transport_fc.h>

#include "csio_scsi.h"
#include "csio_lnode.h"
#include "csio_rnode.h"
#include "csio_hw.h"

#define CSIO_DRV_AUTHOR			"Chelsio Communications"
#define CSIO_DRV_LICENSE		"Dual BSD/GPL"
#define CSIO_DRV_DESC			"Chelsio FCoE driver"
#define CSIO_DRV_VERSION		"1.0.0"

#define CSIO_DEVICE(devid, idx)					\
{ PCI_VENDOR_ID_CHELSIO, (devid), PCI_ANY_ID, PCI_ANY_ID, 0, 0, (idx) }

#define CSIO_IS_T4_FPGA(_dev)		(((_dev) == CSIO_DEVID_PE10K) ||\
					 ((_dev) == CSIO_DEVID_PE10K_PF1))

/* FCoE device IDs */
#define CSIO_DEVID_PE10K		0xA000
#define CSIO_DEVID_PE10K_PF1		0xA001
#define CSIO_DEVID_T440DBG_FCOE		0x4600
#define CSIO_DEVID_T420CR_FCOE		0x4601
#define CSIO_DEVID_T422CR_FCOE		0x4602
#define CSIO_DEVID_T440CR_FCOE		0x4603
#define CSIO_DEVID_T420BCH_FCOE		0x4604
#define CSIO_DEVID_T440BCH_FCOE		0x4605
#define CSIO_DEVID_T440CH_FCOE		0x4606
#define CSIO_DEVID_T420SO_FCOE		0x4607
#define CSIO_DEVID_T420CX_FCOE		0x4608
#define CSIO_DEVID_T420BT_FCOE		0x4609
#define CSIO_DEVID_T404BT_FCOE		0x460A
#define CSIO_DEVID_B420_FCOE		0x460B
#define CSIO_DEVID_B404_FCOE		0x460C
#define CSIO_DEVID_T480CR_FCOE		0x460D
#define CSIO_DEVID_T440LPCR_FCOE	0x460E

extern struct fc_function_template csio_fc_transport_funcs;
extern struct fc_function_template csio_fc_transport_vport_funcs;

void csio_fchost_attr_init(struct csio_lnode *);

/* INTx handlers */
void csio_scsi_intx_handler(struct csio_hw *, void *, uint32_t,
			       struct csio_fl_dma_buf *, void *);

void csio_fwevt_intx_handler(struct csio_hw *, void *, uint32_t,
				struct csio_fl_dma_buf *, void *);

/* Common os lnode APIs */
void csio_lnodes_block_request(struct csio_hw *);
void csio_lnodes_unblock_request(struct csio_hw *);
void csio_lnodes_block_by_port(struct csio_hw *, uint8_t);
void csio_lnodes_unblock_by_port(struct csio_hw *, uint8_t);

struct csio_lnode *csio_shost_init(struct csio_hw *, struct device *, bool,
					struct csio_lnode *);
void csio_shost_exit(struct csio_lnode *);
void csio_lnodes_exit(struct csio_hw *, bool);

static inline struct Scsi_Host *
csio_ln_to_shost(struct csio_lnode *ln)
{
	return container_of((void *)ln, struct Scsi_Host, hostdata[0]);
}

/* SCSI -- locking version of get/put ioreqs  */
static inline struct csio_ioreq *
csio_get_scsi_ioreq_lock(struct csio_hw *hw, struct csio_scsim *scsim)
{
	struct csio_ioreq *ioreq;
	unsigned long flags;

	spin_lock_irqsave(&scsim->freelist_lock, flags);
	ioreq = csio_get_scsi_ioreq(scsim);
	spin_unlock_irqrestore(&scsim->freelist_lock, flags);

	return ioreq;
}

static inline void
csio_put_scsi_ioreq_lock(struct csio_hw *hw, struct csio_scsim *scsim,
			 struct csio_ioreq *ioreq)
{
	unsigned long flags;

	spin_lock_irqsave(&scsim->freelist_lock, flags);
	csio_put_scsi_ioreq(scsim, ioreq);
	spin_unlock_irqrestore(&scsim->freelist_lock, flags);
}

/* Called in interrupt context */
static inline void
csio_put_scsi_ioreq_list_lock(struct csio_hw *hw, struct csio_scsim *scsim,
			      struct list_head *reqlist, int n)
{
	unsigned long flags;

	spin_lock_irqsave(&scsim->freelist_lock, flags);
	csio_put_scsi_ioreq_list(scsim, reqlist, n);
	spin_unlock_irqrestore(&scsim->freelist_lock, flags);
}

/* Called in interrupt context */
static inline void
csio_put_scsi_ddp_list_lock(struct csio_hw *hw, struct csio_scsim *scsim,
			      struct list_head *reqlist, int n)
{
	unsigned long flags;

	spin_lock_irqsave(&hw->lock, flags);
	csio_put_scsi_ddp_list(scsim, reqlist, n);
	spin_unlock_irqrestore(&hw->lock, flags);
}

#endif /* ifndef __CSIO_INIT_H__ */
