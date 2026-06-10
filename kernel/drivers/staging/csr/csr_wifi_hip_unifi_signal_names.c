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
#include "csr_wifi_hip_unifi.h"

struct sig_name {
	s16 id;
	const char *name;
};

static const struct sig_name Unifi_bulkcmd_names[] = {
	{ 0, "SignalCmd" },
	{ 1, "CopyToHost" },
	{ 2, "CopyToHostAck" },
	{ 3, "CopyFromHost" },
	{ 4, "CopyFromHostAck" },
	{ 5, "ClearSlot" },
	{ 6, "CopyOverlay" },
	{ 7, "CopyOverlayAck" },
	{ 8, "CopyFromHostAndClearSlot" },
	{ 15, "Padding" }
};

const char *lookup_bulkcmd_name(u16 id)
{
	if (id < 9)
		return Unifi_bulkcmd_names[id].name;
	if (id == 15)
		return "Padding";

	return "UNKNOWN";
}


