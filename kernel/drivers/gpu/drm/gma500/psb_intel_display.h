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
#ifndef _INTEL_DISPLAY_H_
#define _INTEL_DISPLAY_H_

bool psb_intel_pipe_has_type(struct drm_crtc *crtc, int type);
void psb_intel_crtc_gamma_set(struct drm_crtc *crtc, u16 *red,
			 u16 *green, u16 *blue, uint32_t type, uint32_t size);
void psb_intel_crtc_destroy(struct drm_crtc *crtc);

#endif
