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
#ifndef _BEEP_LOOP_H
#define _BEEP_LOOP_H

#include <beep/bio.h>
#include <beep/blkdev.h>
#include <beep/spinlock.h>
#include <beep/mutex.h>
#include <uapi/beep/loop.h>

/* Possible states of device */
enum {
	Lo_unbound,
	Lo_bound,
	Lo_rundown,
};

struct loop_func_table;

struct loop_device {
	int		lo_number;
	int		lo_refcnt;
	loff_t		lo_offset;
	loff_t		lo_sizelimit;
	int		lo_flags;
	int		(*transfer)(struct loop_device *, int cmd,
				    struct page *raw_page, unsigned raw_off,
				    struct page *loop_page, unsigned loop_off,
				    int size, sector_t real_block);
	char		lo_file_name[LO_NAME_SIZE];
	char		lo_crypt_name[LO_NAME_SIZE];
	char		lo_encrypt_key[LO_KEY_SIZE];
	int		lo_encrypt_key_size;
	struct loop_func_table *lo_encryption;
	__u32           lo_init[2];
	kuid_t		lo_key_owner;	/* Who set the key */
	int		(*ioctl)(struct loop_device *, int cmd, 
				 unsigned long arg); 

	struct file *	lo_backing_file;
	struct block_device *lo_device;
	unsigned	lo_blocksize;
	void		*key_data; 

	gfp_t		old_gfp_mask;

	spinlock_t		lo_lock;
	struct bio_list		lo_bio_list;
	unsigned int		lo_bio_count;
	int			lo_state;
	struct mutex		lo_ctl_mutex;
	struct task_struct	*lo_thread;
	wait_queue_head_t	lo_event;
	/* wait queue for incoming requests */
	wait_queue_head_t	lo_req_wait;

	struct request_queue	*lo_queue;
	struct gendisk		*lo_disk;
};

/* Support for loadable transfer modules */
struct loop_func_table {
	int number;	/* filter type */ 
	int (*transfer)(struct loop_device *lo, int cmd,
			struct page *raw_page, unsigned raw_off,
			struct page *loop_page, unsigned loop_off,
			int size, sector_t real_block);
	int (*init)(struct loop_device *, const struct loop_info64 *); 
	/* release is called from loop_unregister_transfer or clr_fd */
	int (*release)(struct loop_device *); 
	int (*ioctl)(struct loop_device *, int cmd, unsigned long arg);
	struct module *owner;
}; 

int loop_register_transfer(struct loop_func_table *funcs);
int loop_unregister_transfer(int number); 

#endif
