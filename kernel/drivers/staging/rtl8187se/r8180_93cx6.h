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

#include "r8180.h"
#include "r8180_hw.h"

#define EPROM_DELAY 10

#define EPROM_ANAPARAM_ADDRLWORD 0xd
#define EPROM_ANAPARAM_ADDRHWORD 0xe

#define RFCHIPID 0x6
#define	RFCHIPID_INTERSIL 1
#define	RFCHIPID_RFMD 2
#define	RFCHIPID_PHILIPS 3
#define	RFCHIPID_MAXIM 4
#define	RFCHIPID_GCT 5
#define RFCHIPID_RTL8225 9
#define RF_ZEBRA2 11
#define EPROM_TXPW_BASE 0x05
#define RF_ZEBRA4 12
#define RFCHIPID_RTL8255 0xa
#define RF_PARAM 0x19
#define RF_PARAM_DIGPHY_SHIFT 0
#define RF_PARAM_ANTBDEFAULT_SHIFT 1
#define RF_PARAM_CARRIERSENSE_SHIFT 2
#define RF_PARAM_CARRIERSENSE_MASK (3<<2)
#define ENERGY_TRESHOLD 0x17
#define EPROM_VERSION 0x1E
#define MAC_ADR 0x7

#define CIS 0x18

#define	EPROM_TXPW_OFDM_CH1_2 0x20

#define	EPROM_TXPW_CH1_2 0x30

#define RTL818X_EEPROM_CMD_READ		(1 << 0)
#define RTL818X_EEPROM_CMD_WRITE	(1 << 1)
#define RTL818X_EEPROM_CMD_CK		(1 << 2)
#define RTL818X_EEPROM_CMD_CS		(1 << 3)

