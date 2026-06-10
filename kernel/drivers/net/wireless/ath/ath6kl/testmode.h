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
#include "core.h"

#ifdef CONFIG_NL80211_TESTMODE

void ath6kl_tm_rx_event(struct ath6kl *ar, void *buf, size_t buf_len);
int ath6kl_tm_cmd(struct wiphy *wiphy, void *data, int len);

#else

static inline void ath6kl_tm_rx_event(struct ath6kl *ar, void *buf,
				      size_t buf_len)
{
}

static inline int ath6kl_tm_cmd(struct wiphy *wiphy, void *data, int len)
{
	return 0;
}

#endif
