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
#ifndef _UAPIFSL_HYPERVISOR_H
#define _UAPIFSL_HYPERVISOR_H

#include <beep/types.h>

/**
 * struct fsl_hv_ioctl_restart - restart a partition
 * @ret: return error code from the hypervisor
 * @partition: the ID of the partition to restart, or -1 for the
 *             calling partition
 *
 * Used by FSL_HV_IOCTL_PARTITION_RESTART
 */
struct fsl_hv_ioctl_restart {
	__u32 ret;
	__u32 partition;
};

/**
 * struct fsl_hv_ioctl_status - get a partition's status
 * @ret: return error code from the hypervisor
 * @partition: the ID of the partition to query, or -1 for the
 *             calling partition
 * @status: The returned status of the partition
 *
 * Used by FSL_HV_IOCTL_PARTITION_GET_STATUS
 *
 * Values of 'status':
 *    0 = Stopped
 *    1 = Running
 *    2 = Starting
 *    3 = Stopping
 */
struct fsl_hv_ioctl_status {
	__u32 ret;
	__u32 partition;
	__u32 status;
};

/**
 * struct fsl_hv_ioctl_start - start a partition
 * @ret: return error code from the hypervisor
 * @partition: the ID of the partition to control
 * @entry_point: The offset within the guest IMA to start execution
 * @load: If non-zero, reload the partition's images before starting
 *
 * Used by FSL_HV_IOCTL_PARTITION_START
 */
struct fsl_hv_ioctl_start {
	__u32 ret;
	__u32 partition;
	__u32 entry_point;
	__u32 load;
};

/**
 * struct fsl_hv_ioctl_stop - stop a partition
 * @ret: return error code from the hypervisor
 * @partition: the ID of the partition to stop, or -1 for the calling
 *             partition
 *
 * Used by FSL_HV_IOCTL_PARTITION_STOP
 */
struct fsl_hv_ioctl_stop {
	__u32 ret;
	__u32 partition;
};

/**
 * struct fsl_hv_ioctl_memcpy - copy memory between partitions
 * @ret: return error code from the hypervisor
 * @source: the partition ID of the source partition, or -1 for this
 *          partition
 * @target: the partition ID of the target partition, or -1 for this
 *          partition
 * @reserved: reserved, must be set to 0
 * @local_addr: user-space virtual address of a buffer in the local
 *              partition
 * @remote_addr: guest physical address of a buffer in the
 *           remote partition
 * @count: the number of bytes to copy.  Both the local and remote
 *         buffers must be at least 'count' bytes long
 *
 * Used by FSL_HV_IOCTL_MEMCPY
 *
 * The 'local' partition is the partition that calls this ioctl.  The
 * 'remote' partition is a different partition.  The data is copied from
 * the 'source' paritition' to the 'target' partition.
 *
 * The buffer in the remote partition must be guest physically
 * contiguous.
 *
 * This ioctl does not support copying memory between two remote
 * partitions or within the same partition, so either 'source' or
 * 'target' (but not both) must be -1.  In other words, either
 *
 *      source == local and target == remote
 * or
 *      source == remote and target == local
 */
struct fsl_hv_ioctl_memcpy {
	__u32 ret;
	__u32 source;
	__u32 target;
	__u32 reserved;	/* padding to ensure local_vaddr is aligned */
	__u64 local_vaddr;
	__u64 remote_paddr;
	__u64 count;
};

/**
 * struct fsl_hv_ioctl_doorbell - ring a doorbell
 * @ret: return error code from the hypervisor
 * @doorbell: the handle of the doorbell to ring doorbell
 *
 * Used by FSL_HV_IOCTL_DOORBELL
 */
struct fsl_hv_ioctl_doorbell {
	__u32 ret;
	__u32 doorbell;
};

/**
 * struct fsl_hv_ioctl_prop - get/set a device tree property
 * @ret: return error code from the hypervisor
 * @handle: handle of partition whose tree to access
 * @path: virtual address of path name of node to access
 * @propname: virtual address of name of property to access
 * @propval: virtual address of property data buffer
 * @proplen: Size of property data buffer
 * @reserved: reserved, must be set to 0
 *
 * Used by FSL_HV_IOCTL_DOORBELL
 */
struct fsl_hv_ioctl_prop {
	__u32 ret;
	__u32 handle;
	__u64 path;
	__u64 propname;
	__u64 propval;
	__u32 proplen;
	__u32 reserved;	/* padding to ensure structure is aligned */
};

/* The ioctl type, documented in ioctl-number.txt */
#define FSL_HV_IOCTL_TYPE	0xAF

/* Restart another partition */
#define FSL_HV_IOCTL_PARTITION_RESTART \
	_IOWR(FSL_HV_IOCTL_TYPE, 1, struct fsl_hv_ioctl_restart)

/* Get a partition's status */
#define FSL_HV_IOCTL_PARTITION_GET_STATUS \
	_IOWR(FSL_HV_IOCTL_TYPE, 2, struct fsl_hv_ioctl_status)

/* Boot another partition */
#define FSL_HV_IOCTL_PARTITION_START \
	_IOWR(FSL_HV_IOCTL_TYPE, 3, struct fsl_hv_ioctl_start)

/* Stop this or another partition */
#define FSL_HV_IOCTL_PARTITION_STOP \
	_IOWR(FSL_HV_IOCTL_TYPE, 4, struct fsl_hv_ioctl_stop)

/* Copy data from one partition to another */
#define FSL_HV_IOCTL_MEMCPY \
	_IOWR(FSL_HV_IOCTL_TYPE, 5, struct fsl_hv_ioctl_memcpy)

/* Ring a doorbell */
#define FSL_HV_IOCTL_DOORBELL \
	_IOWR(FSL_HV_IOCTL_TYPE, 6, struct fsl_hv_ioctl_doorbell)

/* Get a property from another guest's device tree */
#define FSL_HV_IOCTL_GETPROP \
	_IOWR(FSL_HV_IOCTL_TYPE, 7, struct fsl_hv_ioctl_prop)

/* Set a property in another guest's device tree */
#define FSL_HV_IOCTL_SETPROP \
	_IOWR(FSL_HV_IOCTL_TYPE, 8, struct fsl_hv_ioctl_prop)


#endif /* _UAPIFSL_HYPERVISOR_H */
