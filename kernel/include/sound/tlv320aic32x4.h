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
#ifndef _AIC32X4_PDATA_H
#define _AIC32X4_PDATA_H

#define AIC32X4_PWR_MICBIAS_2075_LDOIN		0x00000001
#define AIC32X4_PWR_AVDD_DVDD_WEAK_DISABLE	0x00000002
#define AIC32X4_PWR_AIC32X4_LDO_ENABLE		0x00000004
#define AIC32X4_PWR_CMMODE_LDOIN_RANGE_18_36	0x00000008
#define AIC32X4_PWR_CMMODE_HP_LDOIN_POWERED	0x00000010

#define AIC32X4_MICPGA_ROUTE_LMIC_IN2R_10K	0x00000001
#define AIC32X4_MICPGA_ROUTE_RMIC_IN1L_10K	0x00000002

struct aic32x4_pdata {
	u32 power_cfg;
	u32 micpga_routing;
	bool swapdacs;
	int rstn_gpio;
};

#endif
