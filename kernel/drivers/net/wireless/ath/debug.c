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
#include <beep/export.h>
#include "ath.h"

const char *ath_opmode_to_string(enum nl80211_iftype opmode)
{
	switch (opmode) {
	case NL80211_IFTYPE_UNSPECIFIED:
		return "UNSPEC";
	case NL80211_IFTYPE_ADHOC:
		return "ADHOC";
	case NL80211_IFTYPE_STATION:
		return "STATION";
	case NL80211_IFTYPE_AP:
		return "AP";
	case NL80211_IFTYPE_AP_VLAN:
		return "AP-VLAN";
	case NL80211_IFTYPE_WDS:
		return "WDS";
	case NL80211_IFTYPE_MONITOR:
		return "MONITOR";
	case NL80211_IFTYPE_MESH_POINT:
		return "MESH";
	case NL80211_IFTYPE_P2P_CLIENT:
		return "P2P-CLIENT";
	case NL80211_IFTYPE_P2P_GO:
		return "P2P-GO";
	default:
		return "UNKNOWN";
	}
}
EXPORT_SYMBOL(ath_opmode_to_string);
