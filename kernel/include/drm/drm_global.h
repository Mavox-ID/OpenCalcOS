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
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-dot-com>
 */

#ifndef _DRM_GLOBAL_H_
#define _DRM_GLOBAL_H_
enum drm_global_types {
	DRM_GLOBAL_TTM_MEM = 0,
	DRM_GLOBAL_TTM_BO,
	DRM_GLOBAL_TTM_OBJECT,
	DRM_GLOBAL_NUM
};

struct drm_global_reference {
	enum drm_global_types global_type;
	size_t size;
	void *object;
	int (*init) (struct drm_global_reference *);
	void (*release) (struct drm_global_reference *);
};

extern void drm_global_init(void);
extern void drm_global_release(void);
extern int drm_global_item_ref(struct drm_global_reference *ref);
extern void drm_global_item_unref(struct drm_global_reference *ref);

#endif
