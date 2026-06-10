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
#ifndef __iwl_leds_h__
#define __iwl_leds_h__


struct iwl_priv;

#define IWL_LED_SOLID 11
#define IWL_DEF_LED_INTRVL cpu_to_le32(1000)

#define IWL_LED_ACTIVITY       (0<<1)
#define IWL_LED_LINK           (1<<1)

void iwlagn_led_enable(struct iwl_priv *priv);
void iwl_leds_init(struct iwl_priv *priv);
void iwl_leds_exit(struct iwl_priv *priv);

#endif /* __iwl_leds_h__ */
