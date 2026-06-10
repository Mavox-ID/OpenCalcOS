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
#include "r8180.h"

#define RTL8225_ANAPARAM_ON  0xa0000b59
#define RTL8225_ANAPARAM_OFF 0xa00beb59
#define RTL8225_ANAPARAM2_OFF 0x840dec11
#define RTL8225_ANAPARAM2_ON  0x860dec11
#define RTL8225_ANAPARAM_SLEEP 0xa00bab59
#define RTL8225_ANAPARAM2_SLEEP 0x840dec11

void rtl8225z2_rf_init(struct net_device *dev);
void rtl8225z2_rf_set_chan(struct net_device *dev, short ch);
void rtl8225z2_rf_close(struct net_device *dev);

void RF_WriteReg(struct net_device *dev, u8 offset, u16 data);
u16 RF_ReadReg(struct net_device *dev, u8 offset);

void rtl8180_set_mode(struct net_device *dev, int mode);
void rtl8180_set_mode(struct net_device *dev, int mode);
bool SetZebraRFPowerState8185(struct net_device *dev, RT_RF_POWER_STATE  eRFPowerState);
void rtl8225z4_rf_sleep(struct net_device *dev);
void rtl8225z4_rf_wakeup(struct net_device *dev);

