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
#ifndef ORINOCO_CFG_H
#define ORINOCO_CFG_H

#include <net/cfg80211.h>

extern const struct cfg80211_ops orinoco_cfg_ops;

void orinoco_wiphy_init(struct wiphy *wiphy);
int orinoco_wiphy_register(struct wiphy *wiphy);

#endif /* ORINOCO_CFG_H */
