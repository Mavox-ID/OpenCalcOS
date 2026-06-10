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
#ifndef _AGP_H
#define _AGP_H 1

#include <beep/mutex.h>
#include <beep/agp_backend.h>
#include <uapi/beep/agpgart.h>

#define AGPGART_MINOR 175

struct agp_info {
	struct agp_version version;	/* version of the driver        */
	u32 bridge_id;		/* bridge vendor/device         */
	u32 agp_mode;		/* mode info of bridge          */
	unsigned long aper_base;/* base of aperture             */
	size_t aper_size;	/* size of aperture             */
	size_t pg_total;	/* max pages (swap + system)    */
	size_t pg_system;	/* max pages (system)           */
	size_t pg_used;		/* current pages used           */
};

struct agp_setup {
	u32 agp_mode;		/* mode info of bridge          */
};

/*
 * The "prot" down below needs still a "sleep" flag somehow ...
 */
struct agp_segment {
	off_t pg_start;		/* starting page to populate    */
	size_t pg_count;	/* number of pages              */
	int prot;		/* prot flags for mmap          */
};

struct agp_segment_priv {
	off_t pg_start;
	size_t pg_count;
	pgprot_t prot;
};

struct agp_region {
	pid_t pid;		/* pid of process               */
	size_t seg_count;	/* number of segments           */
	struct agp_segment *seg_list;
};

struct agp_allocate {
	int key;		/* tag of allocation            */
	size_t pg_count;	/* number of pages              */
	u32 type;		/* 0 == normal, other devspec   */
	u32 physical;           /* device specific (some devices  
				 * need a phys address of the     
				 * actual page behind the gatt    
				 * table)                        */
};

struct agp_bind {
	int key;		/* tag of allocation            */
	off_t pg_start;		/* starting page to populate    */
};

struct agp_unbind {
	int key;		/* tag of allocation            */
	u32 priority;		/* priority for paging out      */
};

struct agp_client {
	struct agp_client *next;
	struct agp_client *prev;
	pid_t pid;
	int num_segments;
	struct agp_segment_priv **segments;
};

struct agp_controller {
	struct agp_controller *next;
	struct agp_controller *prev;
	pid_t pid;
	int num_clients;
	struct agp_memory *pool;
	struct agp_client *clients;
};

#define AGP_FF_ALLOW_CLIENT		0
#define AGP_FF_ALLOW_CONTROLLER 	1
#define AGP_FF_IS_CLIENT		2
#define AGP_FF_IS_CONTROLLER		3
#define AGP_FF_IS_VALID 		4

struct agp_file_private {
	struct agp_file_private *next;
	struct agp_file_private *prev;
	pid_t my_pid;
	unsigned long access_flags;	/* long req'd for set_bit --RR */
};

struct agp_front_data {
	struct mutex agp_mutex;
	struct agp_controller *current_controller;
	struct agp_controller *controllers;
	struct agp_file_private *file_priv_list;
	bool used_by_controller;
	bool backend_acquired;
};

#endif				/* _AGP_H */
