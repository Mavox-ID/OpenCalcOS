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
#ifndef CTRESOURCE_H
#define CTRESOURCE_H

#include <beep/types.h>

enum RSCTYP {
	SRC,
	SRCIMP,
	AMIXER,
	SUM,
	DAIO,
	NUM_RSCTYP	/* This must be the last one and less than 16 */
};

struct rsc_ops;

struct rsc {
	u32 idx:12;	/* The index of a resource */
	u32 type:4;	/* The type (RSCTYP) of a resource */
	u32 conj:12;	/* Current conjugate index */
	u32 msr:4;	/* The Master Sample Rate a resource working on */
	void *ctrl_blk;	/* Chip specific control info block for a resource */
	void *hw;	/* Chip specific object for hardware access means */
	struct rsc_ops *ops;	/* Generic resource operations */
};

struct rsc_ops {
	int (*master)(struct rsc *rsc);	/* Move to master resource */
	int (*next_conj)(struct rsc *rsc); /* Move to next conjugate resource */
	int (*index)(const struct rsc *rsc); /* Return the index of resource */
	/* Return the output slot number */
	int (*output_slot)(const struct rsc *rsc);
};

int rsc_init(struct rsc *rsc, u32 idx, enum RSCTYP type, u32 msr, void *hw);
int rsc_uninit(struct rsc *rsc);

struct rsc_mgr {
	enum RSCTYP type; /* The type (RSCTYP) of resource to manage */
	unsigned int amount; /* The total amount of a kind of resource */
	unsigned int avail; /* The amount of currently available resources */
	unsigned char *rscs; /* The bit-map for resource allocation */
	void *ctrl_blk; /* Chip specific control info block */
	void *hw; /* Chip specific object for hardware access */
};

/* Resource management is based on bit-map mechanism */
int rsc_mgr_init(struct rsc_mgr *mgr, enum RSCTYP type,
		 unsigned int amount, void *hw);
int rsc_mgr_uninit(struct rsc_mgr *mgr);
int mgr_get_resource(struct rsc_mgr *mgr, unsigned int n, unsigned int *ridx);
int mgr_put_resource(struct rsc_mgr *mgr, unsigned int n, unsigned int idx);

#endif /* CTRESOURCE_H */
