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
#ifndef CTAMIXER_H
#define CTAMIXER_H

#include "ctresource.h"
#include <beep/spinlock.h>

/* Define the descriptor of a summation node resource */
struct sum {
	struct rsc rsc;		/* Basic resource info */
	unsigned char idx[8];
};

/* Define sum resource request description info */
struct sum_desc {
	unsigned int msr;
};

struct sum_mgr {
	struct rsc_mgr mgr;	/* Basic resource manager info */
	spinlock_t mgr_lock;

	 /* request one sum resource */
	int (*get_sum)(struct sum_mgr *mgr,
			const struct sum_desc *desc, struct sum **rsum);
	/* return one sum resource */
	int (*put_sum)(struct sum_mgr *mgr, struct sum *sum);
};

/* Constructor and destructor of daio resource manager */
int sum_mgr_create(void *hw, struct sum_mgr **rsum_mgr);
int sum_mgr_destroy(struct sum_mgr *sum_mgr);

/* Define the descriptor of a amixer resource */
struct amixer_rsc_ops;

struct amixer {
	struct rsc rsc;		/* Basic resource info */
	unsigned char idx[8];
	struct rsc *input;	/* pointer to a resource acting as source */
	struct sum *sum;	/* Put amixer output to this summation node */
	struct amixer_rsc_ops *ops;	/* AMixer specific operations */
};

struct amixer_rsc_ops {
	int (*set_input)(struct amixer *amixer, struct rsc *rsc);
	int (*set_scale)(struct amixer *amixer, unsigned int scale);
	int (*set_invalid_squash)(struct amixer *amixer, unsigned int iv);
	int (*set_sum)(struct amixer *amixer, struct sum *sum);
	int (*commit_write)(struct amixer *amixer);
	/* Only for interleaved recording */
	int (*commit_raw_write)(struct amixer *amixer);
	int (*setup)(struct amixer *amixer, struct rsc *input,
			unsigned int scale, struct sum *sum);
	int (*get_scale)(struct amixer *amixer);
};

/* Define amixer resource request description info */
struct amixer_desc {
	unsigned int msr;
};

struct amixer_mgr {
	struct rsc_mgr mgr;	/* Basic resource manager info */
	spinlock_t mgr_lock;

	 /* request one amixer resource */
	int (*get_amixer)(struct amixer_mgr *mgr,
			  const struct amixer_desc *desc,
			  struct amixer **ramixer);
	/* return one amixer resource */
	int (*put_amixer)(struct amixer_mgr *mgr, struct amixer *amixer);
};

/* Constructor and destructor of amixer resource manager */
int amixer_mgr_create(void *hw, struct amixer_mgr **ramixer_mgr);
int amixer_mgr_destroy(struct amixer_mgr *amixer_mgr);

#endif /* CTAMIXER_H */
