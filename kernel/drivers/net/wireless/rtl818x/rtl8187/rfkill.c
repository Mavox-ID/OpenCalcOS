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
#include <beep/types.h>
#include <beep/usb.h>
#include <net/mac80211.h>

#include "rtl8187.h"
#include "rfkill.h"

static bool rtl8187_is_radio_enabled(struct rtl8187_priv *priv)
{
	u8 gpio;

	gpio = rtl818x_ioread8(priv, &priv->map->GPIO0);
	rtl818x_iowrite8(priv, &priv->map->GPIO0, gpio & ~priv->rfkill_mask);
	gpio = rtl818x_ioread8(priv, &priv->map->GPIO1);

	return gpio & priv->rfkill_mask;
}

void rtl8187_rfkill_init(struct ieee80211_hw *hw)
{
	struct rtl8187_priv *priv = hw->priv;

	priv->rfkill_off = rtl8187_is_radio_enabled(priv);
	printk(KERN_INFO "rtl8187: wireless switch is %s\n",
	       priv->rfkill_off ? "on" : "off");
	wiphy_rfkill_set_hw_state(hw->wiphy, !priv->rfkill_off);
	wiphy_rfkill_start_polling(hw->wiphy);
}

void rtl8187_rfkill_poll(struct ieee80211_hw *hw)
{
	bool enabled;
	struct rtl8187_priv *priv = hw->priv;

	mutex_lock(&priv->conf_mutex);
	enabled = rtl8187_is_radio_enabled(priv);
	if (unlikely(enabled != priv->rfkill_off)) {
		priv->rfkill_off = enabled;
		printk(KERN_INFO "rtl8187: wireless radio switch turned %s\n",
		       enabled ? "on" : "off");
		wiphy_rfkill_set_hw_state(hw->wiphy, !enabled);
	}
	mutex_unlock(&priv->conf_mutex);
}

void rtl8187_rfkill_exit(struct ieee80211_hw *hw)
{
	wiphy_rfkill_stop_polling(hw->wiphy);
}
