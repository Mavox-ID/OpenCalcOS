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
#ifndef __WL_PROFILE_H__
#define __WL_PROFILE_H__




/*******************************************************************************
 *  constant definitions
 ******************************************************************************/
#define ROOT_CONFIG_FILENAME "/etc/agere/iwconfig-"


/*******************************************************************************
 *  function prototypes
 ******************************************************************************/
void parse_config( struct net_device *dev );

int readline( int filedesc, char *buffer );

void translate_option( char *buffer, struct wl_private *lp );

int parse_mac_address( char *value, u_char *byte_array );

void ParseConfigLine( char *pszLine, char **ppszLVal, char **ppszRVal );


#endif  // __WL_PROFILE_H__
