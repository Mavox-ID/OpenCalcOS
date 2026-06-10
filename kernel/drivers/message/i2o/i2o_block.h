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
#ifndef I2O_BLOCK_OSM_H
#define I2O_BLOCK_OSM_H

#define I2O_BLOCK_RETRY_TIME HZ/4
#define I2O_BLOCK_MAX_OPEN_REQUESTS 50

/* request queue sizes */
#define I2O_BLOCK_REQ_MEMPOOL_SIZE		32

#define KERNEL_SECTOR_SHIFT 9
#define KERNEL_SECTOR_SIZE (1 << KERNEL_SECTOR_SHIFT)

/* I2O Block OSM mempool struct */
struct i2o_block_mempool {
	struct kmem_cache *slab;
	mempool_t *pool;
};

/* I2O Block device descriptor */
struct i2o_block_device {
	struct i2o_device *i2o_dev;	/* pointer to I2O device */
	struct gendisk *gd;
	spinlock_t lock;	/* queue lock */
	struct list_head open_queue;	/* list of transferred, but unfinished
					   requests */
	unsigned int open_queue_depth;	/* number of requests in the queue */

	int rcache;		/* read cache flags */
	int wcache;		/* write cache flags */
	int flags;
	u16 power;		/* power state */
	int media_change_flag;	/* media changed flag */
};

/* I2O Block device request */
struct i2o_block_request {
	struct list_head queue;
	struct request *req;	/* corresponding request */
	struct i2o_block_device *i2o_blk_dev;	/* I2O block device */
	struct device *dev;	/* device used for DMA */
	int sg_nents;		/* number of SG elements */
	struct scatterlist sg_table[I2O_MAX_PHYS_SEGMENTS];	/* SG table */
};

/* I2O Block device delayed request */
struct i2o_block_delayed_request {
	struct delayed_work work;
	struct request_queue *queue;
};

#endif
