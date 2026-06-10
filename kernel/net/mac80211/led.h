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
#include <beep/list.h>
#include <beep/spinlock.h>
#include <beep/leds.h>
#include "ieee80211_i.h"

#ifdef CONFIG_MAC80211_LEDS
void ieee80211_led_rx(struct ieee80211_local *local);
void ieee80211_led_tx(struct ieee80211_local *local, int q);
void ieee80211_led_assoc(struct ieee80211_local *local,
			 bool associated);
void ieee80211_led_radio(struct ieee80211_local *local,
			 bool enabled);
void ieee80211_led_names(struct ieee80211_local *local);
void ieee80211_led_init(struct ieee80211_local *local);
void ieee80211_led_exit(struct ieee80211_local *local);
void ieee80211_mod_tpt_led_trig(struct ieee80211_local *local,
				unsigned int types_on, unsigned int types_off);
#else
static inline void ieee80211_led_rx(struct ieee80211_local *local)
{
}
static inline void ieee80211_led_tx(struct ieee80211_local *local, int q)
{
}
static inline void ieee80211_led_assoc(struct ieee80211_local *local,
				       bool associated)
{
}
static inline void ieee80211_led_radio(struct ieee80211_local *local,
				       bool enabled)
{
}
static inline void ieee80211_led_names(struct ieee80211_local *local)
{
}
static inline void ieee80211_led_init(struct ieee80211_local *local)
{
}
static inline void ieee80211_led_exit(struct ieee80211_local *local)
{
}
static inline void ieee80211_mod_tpt_led_trig(struct ieee80211_local *local,
					      unsigned int types_on,
					      unsigned int types_off)
{
}
#endif

static inline void
ieee80211_tpt_led_trig_tx(struct ieee80211_local *local, __le16 fc, int bytes)
{
#ifdef CONFIG_MAC80211_LEDS
	if (local->tpt_led_trigger && ieee80211_is_data(fc))
		local->tpt_led_trigger->tx_bytes += bytes;
#endif
}

static inline void
ieee80211_tpt_led_trig_rx(struct ieee80211_local *local, __le16 fc, int bytes)
{
#ifdef CONFIG_MAC80211_LEDS
	if (local->tpt_led_trigger && ieee80211_is_data(fc))
		local->tpt_led_trigger->rx_bytes += bytes;
#endif
}
