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
/*This files contains card eeprom (93c46 or 93c56) programming routines*/
/*memory is addressed by WORDS*/

#include "r8192U.h"
#include "r8192U_hw.h"

#define EPROM_DELAY 10

#define EPROM_ANAPARAM_ADDRLWORD 0xd
#define EPROM_ANAPARAM_ADDRHWORD 0xe

#define EPROM_RFCHIPID 0x6
#define EPROM_TXPW_BASE 0x05
#define EPROM_RFCHIPID_RTL8225U 5
#define EPROM_RF_PARAM 0x4
#define EPROM_CONFIG2 0xc

#define EPROM_VERSION 0x1E
#define MAC_ADR 0x7

#define CIS 0x18

#define EPROM_TXPW0 0x16
#define EPROM_TXPW2 0x1b
#define EPROM_TXPW1 0x3d


u32 eprom_read(struct net_device *dev,u32 addr); //reads a 16 bits word
