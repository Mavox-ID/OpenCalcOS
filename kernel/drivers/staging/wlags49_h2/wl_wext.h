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
#ifndef __WL_WEXT_H__
#define __WL_WEXT_H__


/*******************************************************************************
 *  function protoypes
 ******************************************************************************/

struct iw_statistics *wl_wireless_stats( struct net_device *dev );

struct iw_statistics * wl_get_wireless_stats( struct net_device *dev );

inline void wl_spy_gather (struct net_device *dev, u_char *mac);

void wl_wext_event_freq( struct net_device *dev );
void wl_wext_event_mode( struct net_device *dev );
void wl_wext_event_essid( struct net_device *dev );
void wl_wext_event_encode( struct net_device *dev );
void wl_wext_event_ap( struct net_device *dev );
void wl_wext_event_scan_complete( struct net_device *dev );
void wl_wext_event_new_sta( struct net_device *dev );
void wl_wext_event_expired_sta( struct net_device *dev );
void wl_wext_event_mic_failed( struct net_device *dev );
void wl_wext_event_assoc_ie( struct net_device *dev );

extern const struct iw_handler_def wl_iw_handler_def;

#endif  // __WL_WEXT_H__
