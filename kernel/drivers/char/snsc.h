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
 * This file contains macros and data types for communication with the
 * system controllers in SGI SN systems.
 */

#ifndef _SN_SYSCTL_H_
#define _SN_SYSCTL_H_

#include <beep/types.h>
#include <beep/spinlock.h>
#include <beep/wait.h>
#include <beep/fs.h>
#include <beep/cdev.h>
#include <beep/semaphore.h>
#include <asm/sn/types.h>

#define CHUNKSIZE 127

/* This structure is used to track an open subchannel. */
struct subch_data_s {
	nasid_t sd_nasid;	/* node on which the subchannel was opened */
	int sd_subch;		/* subchannel number */
	spinlock_t sd_rlock;	/* monitor lock for rsv */
	spinlock_t sd_wlock;	/* monitor lock for wsv */
	wait_queue_head_t sd_rq;	/* wait queue for readers */
	wait_queue_head_t sd_wq;	/* wait queue for writers */
	struct semaphore sd_rbs;	/* semaphore for read buffer */
	struct semaphore sd_wbs;	/* semaphore for write buffer */

	char sd_rb[CHUNKSIZE];	/* read buffer */
	char sd_wb[CHUNKSIZE];	/* write buffer */
};

struct sysctl_data_s {
	struct cdev scd_cdev;	/* Character device info */
	nasid_t scd_nasid;	/* Node on which subchannels are opened. */
};


/* argument types */
#define IR_ARG_INT              0x00    /* 4-byte integer (big-endian)  */
#define IR_ARG_ASCII            0x01    /* null-terminated ASCII string */
#define IR_ARG_UNKNOWN          0x80    /* unknown data type.  The low
                                         * 7 bits will contain the data
                                         * length.                      */
#define IR_ARG_UNKNOWN_LENGTH_MASK	0x7f


/* system controller event codes */
#define EV_CLASS_MASK		0xf000ul
#define EV_SEVERITY_MASK	0x0f00ul
#define EV_COMPONENT_MASK	0x00fful

#define EV_CLASS_POWER		0x1000ul
#define EV_CLASS_FAN		0x2000ul
#define EV_CLASS_TEMP		0x3000ul
#define EV_CLASS_ENV		0x4000ul
#define EV_CLASS_TEST_FAULT	0x5000ul
#define EV_CLASS_TEST_WARNING	0x6000ul
#define EV_CLASS_PWRD_NOTIFY	0x8000ul

/* ENV class codes */
#define ENV_PWRDN_PEND		0x4101ul

#define EV_SEVERITY_POWER_STABLE	0x0000ul
#define EV_SEVERITY_POWER_LOW_WARNING	0x0100ul
#define EV_SEVERITY_POWER_HIGH_WARNING	0x0200ul
#define EV_SEVERITY_POWER_HIGH_FAULT	0x0300ul
#define EV_SEVERITY_POWER_LOW_FAULT	0x0400ul

#define EV_SEVERITY_FAN_STABLE		0x0000ul
#define EV_SEVERITY_FAN_WARNING		0x0100ul
#define EV_SEVERITY_FAN_FAULT		0x0200ul

#define EV_SEVERITY_TEMP_STABLE		0x0000ul
#define EV_SEVERITY_TEMP_ADVISORY	0x0100ul
#define EV_SEVERITY_TEMP_CRITICAL	0x0200ul
#define EV_SEVERITY_TEMP_FAULT		0x0300ul

void scdrv_event_init(struct sysctl_data_s *);

#endif /* _SN_SYSCTL_H_ */
