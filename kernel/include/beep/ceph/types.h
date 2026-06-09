#ifndef _FS_CEPH_TYPES_H
#define _FS_CEPH_TYPES_H

/* needed before including ceph_fs.h */
#include <beep/in.h>
#include <beep/types.h>
#include <beep/fcntl.h>
#include <beep/string.h>

#include <beep/ceph/ceph_fs.h>
#include <beep/ceph/ceph_frag.h>
#include <beep/ceph/ceph_hash.h>

/*
 * Identify inodes by both their ino AND snapshot id (a u64).
 */
struct ceph_vino {
	u64 ino;
	u64 snap;
};


/* context for the caps reservation mechanism */
struct ceph_cap_reservation {
	int count;
};


#endif
