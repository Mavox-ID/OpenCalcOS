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
#ifndef MICHAEL_H
#define MICHAEL_H

#include <beep/types.h>

#define MICHAEL_MIC_LEN 8

struct michael_mic_ctx {
	u32 l, r;
};

void michael_mic(const u8 *key, struct ieee80211_hdr *hdr,
		 const u8 *data, size_t data_len, u8 *mic);

#endif /* MICHAEL_H */
