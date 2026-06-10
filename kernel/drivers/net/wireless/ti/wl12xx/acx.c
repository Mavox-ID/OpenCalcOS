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
#include "../wlcore/cmd.h"
#include "../wlcore/debug.h"
#include "../wlcore/acx.h"

#include "acx.h"

int wl1271_acx_host_if_cfg_bitmap(struct wl1271 *wl, u32 host_cfg_bitmap)
{
	struct wl1271_acx_host_config_bitmap *bitmap_conf;
	int ret;

	bitmap_conf = kzalloc(sizeof(*bitmap_conf), GFP_KERNEL);
	if (!bitmap_conf) {
		ret = -ENOMEM;
		goto out;
	}

	bitmap_conf->host_cfg_bitmap = cpu_to_le32(host_cfg_bitmap);

	ret = wl1271_cmd_configure(wl, ACX_HOST_IF_CFG_BITMAP,
				   bitmap_conf, sizeof(*bitmap_conf));
	if (ret < 0) {
		wl1271_warning("wl1271 bitmap config opt failed: %d", ret);
		goto out;
	}

out:
	kfree(bitmap_conf);

	return ret;
}
