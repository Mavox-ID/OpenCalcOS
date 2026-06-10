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
#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include <drm/drmP.h>
#include <drm/drm_fb_helper.h>

#include "psb_drv.h"

struct psb_framebuffer {
	struct drm_framebuffer base;
	struct address_space *addr_space;
	struct fb_info *fbdev;
	struct gtt_range *gtt;
};

struct psb_fbdev {
	struct drm_fb_helper psb_fb_helper;
	struct psb_framebuffer pfb;
};

#define to_psb_fb(x) container_of(x, struct psb_framebuffer, base)

extern int psb_intel_connector_clones(struct drm_device *dev, int type_mask);

#endif

