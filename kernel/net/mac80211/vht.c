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
#include <beep/ieee80211.h>
#include <beep/export.h>
#include <net/mac80211.h>
#include "ieee80211_i.h"


void ieee80211_vht_cap_ie_to_sta_vht_cap(struct ieee80211_sub_if_data *sdata,
					 struct ieee80211_supported_band *sband,
					 struct ieee80211_vht_cap *vht_cap_ie,
					 struct ieee80211_sta_vht_cap *vht_cap)
{
	if (WARN_ON_ONCE(!vht_cap))
		return;

	memset(vht_cap, 0, sizeof(*vht_cap));

	if (!vht_cap_ie || !sband->vht_cap.vht_supported)
		return;

	vht_cap->vht_supported = true;

	vht_cap->cap = le32_to_cpu(vht_cap_ie->vht_cap_info);

	/* Copy peer MCS info, the driver might need them. */
	memcpy(&vht_cap->vht_mcs, &vht_cap_ie->supp_mcs,
	       sizeof(struct ieee80211_vht_mcs_info));
}
