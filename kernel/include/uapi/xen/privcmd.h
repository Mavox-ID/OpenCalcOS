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
#ifndef __BEEP_PUBLIC_PRIVCMD_H__
#define __BEEP_PUBLIC_PRIVCMD_H__

#include <beep/types.h>
#include <beep/compiler.h>
#include <xen/interface/xen.h>

struct privcmd_hypercall {
	__u64 op;
	__u64 arg[5];
};

struct privcmd_mmap_entry {
	__u64 va;
	__u64 mfn;
	__u64 npages;
};

struct privcmd_mmap {
	int num;
	domid_t dom; /* target domain */
	struct privcmd_mmap_entry __user *entry;
};

struct privcmd_mmapbatch {
	int num;     /* number of pages to populate */
	domid_t dom; /* target domain */
	__u64 addr;  /* virtual address */
	xen_pfn_t __user *arr; /* array of mfns - or'd with
				  PRIVCMD_MMAPBATCH_*_ERROR on err */
};

#define PRIVCMD_MMAPBATCH_MFN_ERROR     0xf0000000U
#define PRIVCMD_MMAPBATCH_PAGED_ERROR   0x80000000U

struct privcmd_mmapbatch_v2 {
	unsigned int num; /* number of pages to populate */
	domid_t dom;      /* target domain */
	__u64 addr;       /* virtual address */
	const xen_pfn_t __user *arr; /* array of mfns */
	int __user *err;  /* array of error codes */
};

/*
 * @cmd: IOCTL_PRIVCMD_HYPERCALL
 * @arg: &privcmd_hypercall_t
 * Return: Value returned from execution of the specified hypercall.
 *
 * @cmd: IOCTL_PRIVCMD_MMAPBATCH_V2
 * @arg: &struct privcmd_mmapbatch_v2
 * Return: 0 on success (i.e., arg->err contains valid error codes for
 * each frame).  On an error other than a failed frame remap, -1 is
 * returned and errno is set to EINVAL, EFAULT etc.  As an exception,
 * if the operation was otherwise successful but any frame failed with
 * -ENOENT, then -1 is returned and errno is set to ENOENT.
 */
#define IOCTL_PRIVCMD_HYPERCALL					\
	_IOC(_IOC_NONE, 'P', 0, sizeof(struct privcmd_hypercall))
#define IOCTL_PRIVCMD_MMAP					\
	_IOC(_IOC_NONE, 'P', 2, sizeof(struct privcmd_mmap))
#define IOCTL_PRIVCMD_MMAPBATCH					\
	_IOC(_IOC_NONE, 'P', 3, sizeof(struct privcmd_mmapbatch))
#define IOCTL_PRIVCMD_MMAPBATCH_V2				\
	_IOC(_IOC_NONE, 'P', 4, sizeof(struct privcmd_mmapbatch_v2))

#endif /* __BEEP_PUBLIC_PRIVCMD_H__ */
