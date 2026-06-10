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
 * Copyright 2002 Tungsten Graphics, Inc., Cedar Park, Texas.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _DRM_SAREA_H_
#define _DRM_SAREA_H_

#include <drm/drm.h>

/* SAREA area needs to be at least a page */
#if defined(__alpha__)
#define SAREA_MAX                       0x2000U
#elif defined(__mips__)
#define SAREA_MAX                       0x4000U
#elif defined(__ia64__)
#define SAREA_MAX                       0x10000U	/* 64kB */
#else
/* Intel 830M driver needs at least 8k SAREA */
#define SAREA_MAX                       0x2000U
#endif

/** Maximum number of drawables in the SAREA */
#define SAREA_MAX_DRAWABLES		256

#define SAREA_DRAWABLE_CLAIMED_ENTRY    0x80000000

/** SAREA drawable */
struct drm_sarea_drawable {
	unsigned int stamp;
	unsigned int flags;
};

/** SAREA frame */
struct drm_sarea_frame {
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
	unsigned int fullscreen;
};

/** SAREA */
struct drm_sarea {
    /** first thing is always the DRM locking structure */
	struct drm_hw_lock lock;
    /** \todo Use readers/writer lock for drm_sarea::drawable_lock */
	struct drm_hw_lock drawable_lock;
	struct drm_sarea_drawable drawableTable[SAREA_MAX_DRAWABLES];	/**< drawables */
	struct drm_sarea_frame frame;	/**< frame */
	drm_context_t dummy_context;
};

#ifndef __KERNEL__
typedef struct drm_sarea_drawable drm_sarea_drawable_t;
typedef struct drm_sarea_frame drm_sarea_frame_t;
typedef struct drm_sarea drm_sarea_t;
#endif

#endif				/* _DRM_SAREA_H_ */
