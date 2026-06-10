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
#ifndef __NV50_DISPLAY_H__
#define __NV50_DISPLAY_H__

#include "nouveau_display.h"
#include "nouveau_crtc.h"
#include "nouveau_reg.h"

int  nv50_display_create(struct drm_device *);
void nv50_display_destroy(struct drm_device *);
int  nv50_display_init(struct drm_device *);
void nv50_display_fini(struct drm_device *);

void nv50_display_flip_stop(struct drm_crtc *);
int  nv50_display_flip_next(struct drm_crtc *, struct drm_framebuffer *,
			    struct nouveau_channel *, u32 swap_interval);

struct nouveau_bo *nv50_display_crtc_sema(struct drm_device *, int head);

#endif /* __NV50_DISPLAY_H__ */
