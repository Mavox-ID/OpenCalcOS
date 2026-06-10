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
#ifndef _ORINOCO_SCAN_H_
#define _ORINOCO_SCAN_H_

/* Forward declarations */
struct orinoco_private;
struct agere_ext_scan_info;

/* Add scan results */
void orinoco_add_extscan_result(struct orinoco_private *priv,
				struct agere_ext_scan_info *atom,
				size_t len);
void orinoco_add_hostscan_results(struct orinoco_private *dev,
				  unsigned char *buf,
				  size_t len);
void orinoco_scan_done(struct orinoco_private *priv, bool abort);

#endif /* _ORINOCO_SCAN_H_ */
