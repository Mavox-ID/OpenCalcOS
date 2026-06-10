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
#define MAC_PARTITION_MAGIC	0x504d

/* type field value for A/UX or other Unix partitions */
#define APPLE_AUX_TYPE	"Apple_UNIX_SVR2"

struct mac_partition {
	__be16	signature;	/* expected to be MAC_PARTITION_MAGIC */
	__be16	res1;
	__be32	map_count;	/* # blocks in partition map */
	__be32	start_block;	/* absolute starting block # of partition */
	__be32	block_count;	/* number of blocks in partition */
	char	name[32];	/* partition name */
	char	type[32];	/* string type description */
	__be32	data_start;	/* rel block # of first data block */
	__be32	data_count;	/* number of data blocks */
	__be32	status;		/* partition status bits */
	__be32	boot_start;
	__be32	boot_size;
	__be32	boot_load;
	__be32	boot_load2;
	__be32	boot_entry;
	__be32	boot_entry2;
	__be32	boot_cksum;
	char	processor[16];	/* identifies ISA of boot */
	/* there is more stuff after this that we don't need */
};

#define MAC_STATUS_BOOTABLE	8	/* partition is bootable */

#define MAC_DRIVER_MAGIC	0x4552

/* Driver descriptor structure, in block 0 */
struct mac_driver_desc {
	__be16	signature;	/* expected to be MAC_DRIVER_MAGIC */
	__be16	block_size;
	__be32	block_count;
    /* ... more stuff */
};

int mac_partition(struct parsed_partitions *state);
