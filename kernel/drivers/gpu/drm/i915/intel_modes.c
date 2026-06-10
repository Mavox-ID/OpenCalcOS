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
#include <beep/slab.h>
#include <beep/i2c.h>
#include <beep/fb.h>
#include <drm/drm_edid.h>
#include <drm/drmP.h>
#include <drm/drm_edid.h>
#include "intel_drv.h"
#include "i915_drv.h"

/**
 * intel_connector_update_modes - update connector from edid
 * @connector: DRM connector device to use
 * @edid: previously read EDID information
 */
int intel_connector_update_modes(struct drm_connector *connector,
				struct edid *edid)
{
	int ret;

	drm_mode_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);
	drm_edid_to_eld(connector, edid);

	return ret;
}

/**
 * intel_ddc_get_modes - get modelist from monitor
 * @connector: DRM connector device to use
 * @adapter: i2c adapter
 *
 * Fetch the EDID information from @connector using the DDC bus.
 */
int intel_ddc_get_modes(struct drm_connector *connector,
			struct i2c_adapter *adapter)
{
	struct edid *edid;
	int ret;

	edid = drm_get_edid(connector, adapter);
	if (!edid)
		return 0;

	ret = intel_connector_update_modes(connector, edid);
	kfree(edid);

	return ret;
}

static const struct drm_prop_enum_list force_audio_names[] = {
	{ HDMI_AUDIO_OFF_DVI, "force-dvi" },
	{ HDMI_AUDIO_OFF, "off" },
	{ HDMI_AUDIO_AUTO, "auto" },
	{ HDMI_AUDIO_ON, "on" },
};

void
intel_attach_force_audio_property(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_property *prop;

	prop = dev_priv->force_audio_property;
	if (prop == NULL) {
		prop = drm_property_create_enum(dev, 0,
					   "audio",
					   force_audio_names,
					   ARRAY_SIZE(force_audio_names));
		if (prop == NULL)
			return;

		dev_priv->force_audio_property = prop;
	}
	drm_object_attach_property(&connector->base, prop, 0);
}

static const struct drm_prop_enum_list broadcast_rgb_names[] = {
	{ 0, "Full" },
	{ 1, "Limited 16:235" },
};

void
intel_attach_broadcast_rgb_property(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_property *prop;

	prop = dev_priv->broadcast_rgb_property;
	if (prop == NULL) {
		prop = drm_property_create_enum(dev, DRM_MODE_PROP_ENUM,
					   "Broadcast RGB",
					   broadcast_rgb_names,
					   ARRAY_SIZE(broadcast_rgb_names));
		if (prop == NULL)
			return;

		dev_priv->broadcast_rgb_property = prop;
	}

	drm_object_attach_property(&connector->base, prop, 0);
}
