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
#ifndef _UAPI_AGP_H
#define _UAPI_AGP_H

#define AGPIOC_BASE       'A'
#define AGPIOC_INFO       _IOR (AGPIOC_BASE, 0, struct agp_info*)
#define AGPIOC_ACQUIRE    _IO  (AGPIOC_BASE, 1)
#define AGPIOC_RELEASE    _IO  (AGPIOC_BASE, 2)
#define AGPIOC_SETUP      _IOW (AGPIOC_BASE, 3, struct agp_setup*)
#define AGPIOC_RESERVE    _IOW (AGPIOC_BASE, 4, struct agp_region*)
#define AGPIOC_PROTECT    _IOW (AGPIOC_BASE, 5, struct agp_region*)
#define AGPIOC_ALLOCATE   _IOWR(AGPIOC_BASE, 6, struct agp_allocate*)
#define AGPIOC_DEALLOCATE _IOW (AGPIOC_BASE, 7, int)
#define AGPIOC_BIND       _IOW (AGPIOC_BASE, 8, struct agp_bind*)
#define AGPIOC_UNBIND     _IOW (AGPIOC_BASE, 9, struct agp_unbind*)
#define AGPIOC_CHIPSET_FLUSH _IO (AGPIOC_BASE, 10)

#define AGP_DEVICE      "/dev/agpgart"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef __KERNEL__
#include <beep/types.h>

struct agp_version {
	__u16 major;
	__u16 minor;
};

typedef struct _agp_info {
	struct agp_version version;	/* version of the driver        */
	__u32 bridge_id;	/* bridge vendor/device         */
	__u32 agp_mode;		/* mode info of bridge          */
	unsigned long aper_base;/* base of aperture             */
	size_t aper_size;	/* size of aperture             */
	size_t pg_total;	/* max pages (swap + system)    */
	size_t pg_system;	/* max pages (system)           */
	size_t pg_used;		/* current pages used           */
} agp_info;

typedef struct _agp_setup {
	__u32 agp_mode;		/* mode info of bridge          */
} agp_setup;

/*
 * The "prot" down below needs still a "sleep" flag somehow ...
 */
typedef struct _agp_segment {
	__kernel_off_t pg_start;	/* starting page to populate    */
	__kernel_size_t pg_count;	/* number of pages              */
	int prot;			/* prot flags for mmap          */
} agp_segment;

typedef struct _agp_region {
	__kernel_pid_t pid;		/* pid of process       */
	__kernel_size_t seg_count;	/* number of segments   */
	struct _agp_segment *seg_list;
} agp_region;

typedef struct _agp_allocate {
	int key;		/* tag of allocation            */
	__kernel_size_t pg_count;/* number of pages             */
	__u32 type;		/* 0 == normal, other devspec   */
   	__u32 physical;         /* device specific (some devices  
				 * need a phys address of the     
				 * actual page behind the gatt    
				 * table)                        */
} agp_allocate;

typedef struct _agp_bind {
	int key;		/* tag of allocation            */
	__kernel_off_t pg_start;/* starting page to populate    */
} agp_bind;

typedef struct _agp_unbind {
	int key;		/* tag of allocation            */
	__u32 priority;		/* priority for paging out      */
} agp_unbind;

#endif				/* __KERNEL__ */

#endif /* _UAPI_AGP_H */
