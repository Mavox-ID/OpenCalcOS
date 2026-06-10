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
#ifndef VMWGFX_KMS_H_
#define VMWGFX_KMS_H_

#include <drm/drmP.h>
#include <drm/drm_crtc_helper.h>
#include "vmwgfx_drv.h"

#define VMWGFX_NUM_DISPLAY_UNITS 8


#define vmw_framebuffer_to_vfb(x) \
	container_of(x, struct vmw_framebuffer, base)

/**
 * Base class for framebuffers
 *
 * @pin is called the when ever a crtc uses this framebuffer
 * @unpin is called
 */
struct vmw_framebuffer {
	struct drm_framebuffer base;
	int (*pin)(struct vmw_framebuffer *fb);
	int (*unpin)(struct vmw_framebuffer *fb);
	bool dmabuf;
	struct ttm_base_object *user_obj;
	uint32_t user_handle;
};


#define vmw_crtc_to_du(x) \
	container_of(x, struct vmw_display_unit, crtc)

/*
 * Basic cursor manipulation
 */
int vmw_cursor_update_image(struct vmw_private *dev_priv,
			    u32 *image, u32 width, u32 height,
			    u32 hotspotX, u32 hotspotY);
int vmw_cursor_update_dmabuf(struct vmw_private *dev_priv,
			     struct vmw_dma_buffer *dmabuf,
			     u32 width, u32 height,
			     u32 hotspotX, u32 hotspotY);
void vmw_cursor_update_position(struct vmw_private *dev_priv,
				bool show, int x, int y);


/**
 * Base class display unit.
 *
 * Since the SVGA hw doesn't have a concept of a crtc, encoder or connector
 * so the display unit is all of them at the same time. This is true for both
 * legacy multimon and screen objects.
 */
struct vmw_display_unit {
	struct drm_crtc crtc;
	struct drm_encoder encoder;
	struct drm_connector connector;

	struct vmw_surface *cursor_surface;
	struct vmw_dma_buffer *cursor_dmabuf;
	size_t cursor_age;

	int cursor_x;
	int cursor_y;

	int hotspot_x;
	int hotspot_y;

	unsigned unit;

	/*
	 * Prefered mode tracking.
	 */
	unsigned pref_width;
	unsigned pref_height;
	bool pref_active;
	struct drm_display_mode *pref_mode;

	/*
	 * Gui positioning
	 */
	int gui_x;
	int gui_y;
	bool is_implicit;
};

#define vmw_crtc_to_du(x) \
	container_of(x, struct vmw_display_unit, crtc)
#define vmw_connector_to_du(x) \
	container_of(x, struct vmw_display_unit, connector)


/*
 * Shared display unit functions - vmwgfx_kms.c
 */
void vmw_display_unit_cleanup(struct vmw_display_unit *du);
int vmw_du_page_flip(struct drm_crtc *crtc,
		     struct drm_framebuffer *fb,
		     struct drm_pending_vblank_event *event);
void vmw_du_crtc_save(struct drm_crtc *crtc);
void vmw_du_crtc_restore(struct drm_crtc *crtc);
void vmw_du_crtc_gamma_set(struct drm_crtc *crtc,
			   u16 *r, u16 *g, u16 *b,
			   uint32_t start, uint32_t size);
int vmw_du_crtc_cursor_set(struct drm_crtc *crtc, struct drm_file *file_priv,
			   uint32_t handle, uint32_t width, uint32_t height);
int vmw_du_crtc_cursor_move(struct drm_crtc *crtc, int x, int y);
void vmw_du_connector_dpms(struct drm_connector *connector, int mode);
void vmw_du_connector_save(struct drm_connector *connector);
void vmw_du_connector_restore(struct drm_connector *connector);
enum drm_connector_status
vmw_du_connector_detect(struct drm_connector *connector, bool force);
int vmw_du_connector_fill_modes(struct drm_connector *connector,
				uint32_t max_width, uint32_t max_height);
int vmw_du_connector_set_property(struct drm_connector *connector,
				  struct drm_property *property,
				  uint64_t val);


/*
 * Legacy display unit functions - vmwgfx_ldu.c
 */
int vmw_kms_init_legacy_display_system(struct vmw_private *dev_priv);
int vmw_kms_close_legacy_display_system(struct vmw_private *dev_priv);

/*
 * Screen Objects display functions - vmwgfx_scrn.c
 */
int vmw_kms_init_screen_object_display(struct vmw_private *dev_priv);
int vmw_kms_close_screen_object_display(struct vmw_private *dev_priv);
int vmw_kms_sou_update_layout(struct vmw_private *dev_priv, unsigned num,
			      struct drm_vmw_rect *rects);
bool vmw_kms_screen_object_flippable(struct vmw_private *dev_priv,
				     struct drm_crtc *crtc);
void vmw_kms_screen_object_update_implicit_fb(struct vmw_private *dev_priv,
					      struct drm_crtc *crtc);


#endif
