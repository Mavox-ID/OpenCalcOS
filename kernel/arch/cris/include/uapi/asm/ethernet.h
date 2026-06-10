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
#ifndef _CRIS_ETHERNET_H
#define _CRIS_ETHERNET_H
#define SET_ETH_SPEED_AUTO      SIOCDEVPRIVATE          /* Auto neg speed */
#define SET_ETH_SPEED_10        SIOCDEVPRIVATE+1        /* 10 Mbps */
#define SET_ETH_SPEED_100       SIOCDEVPRIVATE+2        /* 100 Mbps. */
#define SET_ETH_DUPLEX_AUTO     SIOCDEVPRIVATE+3        /* Auto neg duplex */
#define SET_ETH_DUPLEX_HALF     SIOCDEVPRIVATE+4        /* Full duplex */
#define SET_ETH_DUPLEX_FULL     SIOCDEVPRIVATE+5        /* Half duplex */
#define SET_ETH_ENABLE_LEDS     SIOCDEVPRIVATE+6        /* Enable net LEDs */
#define SET_ETH_DISABLE_LEDS    SIOCDEVPRIVATE+7        /* Disable net LEDs */
#define SET_ETH_AUTONEG         SIOCDEVPRIVATE+8
#endif /* _CRIS_ETHERNET_H */
