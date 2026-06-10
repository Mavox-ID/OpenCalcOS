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
#ifndef __CSIO_RNODE_H__
#define __CSIO_RNODE_H__

#include "csio_defs.h"

/* State machine evets */
enum csio_rn_ev {
	CSIO_RNFE_NONE = (uint32_t)0,			/* None */
	CSIO_RNFE_LOGGED_IN,				/* [N/F]Port login
							 * complete.
							 */
	CSIO_RNFE_PRLI_DONE,				/* PRLI completed */
	CSIO_RNFE_PLOGI_RECV,				/* Received PLOGI */
	CSIO_RNFE_PRLI_RECV,				/* Received PLOGI */
	CSIO_RNFE_LOGO_RECV,				/* Received LOGO */
	CSIO_RNFE_PRLO_RECV,				/* Received PRLO */
	CSIO_RNFE_DOWN,					/* Rnode is down */
	CSIO_RNFE_CLOSE,				/* Close rnode */
	CSIO_RNFE_NAME_MISSING,				/* Rnode name missing
							 * in name server.
							 */
	CSIO_RNFE_MAX_EVENT,
};

/* rnode stats */
struct csio_rnode_stats {
	uint32_t	n_err;		/* error */
	uint32_t	n_err_inval;	/* invalid parameter */
	uint32_t	n_err_nomem;	/* error nomem */
	uint32_t	n_evt_unexp;	/* unexpected event */
	uint32_t	n_evt_drop;	/* unexpected event */
	uint32_t	n_evt_fw[RSCN_DEV_LOST];	/* fw events */
	enum csio_rn_ev	n_evt_sm[CSIO_RNFE_MAX_EVENT];	/* State m/c events */
	uint32_t	n_lun_rst;	/* Number of resets of
					 * of LUNs under this
					 * target
					 */
	uint32_t	n_lun_rst_fail;	/* Number of LUN reset
					 * failures.
					 */
	uint32_t	n_tgt_rst;	/* Number of target resets */
	uint32_t	n_tgt_rst_fail;	/* Number of target reset
					 * failures.
					 */
};

/* Defines for rnode role */
#define	CSIO_RNFR_INITIATOR	0x1
#define	CSIO_RNFR_TARGET	0x2
#define CSIO_RNFR_FABRIC	0x4
#define	CSIO_RNFR_NS		0x8
#define CSIO_RNFR_NPORT		0x10

struct csio_rnode {
	struct csio_sm		sm;			/* State machine -
							 * should be the
							 * 1st member
							 */
	struct csio_lnode	*lnp;			/* Pointer to owning
							 * Lnode */
	uint32_t		flowid;			/* Firmware ID */
	struct list_head	host_cmpl_q;		/* SCSI IOs
							 * pending to completed
							 * to Mid-layer.
							 */
	/* FC identifiers for remote node */
	uint32_t		nport_id;
	uint16_t		fcp_flags;		/* FCP Flags */
	uint8_t			cur_evt;		/* Current event */
	uint8_t			prev_evt;		/* Previous event */
	uint32_t		role;			/* Fabric/Target/
							 * Initiator/NS
							 */
	struct fcoe_rdev_entry		*rdev_entry;	/* Rdev entry */
	struct csio_service_parms	rn_sparm;

	/* FC transport attributes */
	struct fc_rport		*rport;		/* FC transport rport */
	uint32_t		supp_classes;	/* Supported FC classes */
	uint32_t		maxframe_size;	/* Max Frame size */
	uint32_t		scsi_id;	/* Transport given SCSI id */

	struct csio_rnode_stats	stats;		/* Common rnode stats */
};

#define csio_rn_flowid(rn)			((rn)->flowid)
#define csio_rn_wwpn(rn)			((rn)->rn_sparm.wwpn)
#define csio_rn_wwnn(rn)			((rn)->rn_sparm.wwnn)
#define csio_rnode_to_lnode(rn)			((rn)->lnp)

int csio_is_rnode_ready(struct csio_rnode *rn);
void csio_rnode_state_to_str(struct csio_rnode *rn, int8_t *str);

struct csio_rnode *csio_rnode_lookup_portid(struct csio_lnode *, uint32_t);
struct csio_rnode *csio_confirm_rnode(struct csio_lnode *,
					  uint32_t, struct fcoe_rdev_entry *);

void csio_rnode_fwevt_handler(struct csio_rnode *rn, uint8_t fwevt);

void csio_put_rnode(struct csio_lnode *ln, struct csio_rnode *rn);

void csio_reg_rnode(struct csio_rnode *);
void csio_unreg_rnode(struct csio_rnode *);

void csio_rnode_devloss_handler(struct csio_rnode *);

#endif /* ifndef __CSIO_RNODE_H__ */
