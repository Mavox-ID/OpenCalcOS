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
extern const struct drm_crtc_helper_funcs cdv_intel_helper_funcs;
extern const struct drm_crtc_funcs cdv_intel_crtc_funcs;
extern void cdv_intel_crt_init(struct drm_device *dev,
			struct psb_intel_mode_device *mode_dev);
extern void cdv_intel_lvds_init(struct drm_device *dev,
			struct psb_intel_mode_device *mode_dev);
extern void cdv_hdmi_init(struct drm_device *dev, struct psb_intel_mode_device *mode_dev,
			int reg);
extern struct drm_display_mode *cdv_intel_crtc_mode_get(struct drm_device *dev,
					     struct drm_crtc *crtc);

static inline void cdv_intel_wait_for_vblank(struct drm_device *dev)
{
	/* Wait for 20ms, i.e. one cycle at 50hz. */
        /* FIXME: msleep ?? */
	mdelay(20);
}


