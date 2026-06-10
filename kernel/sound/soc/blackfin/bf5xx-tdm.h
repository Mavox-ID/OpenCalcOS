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
#ifndef _BF5XX_TDM_H
#define _BF5XX_TDM_H

#define BFIN_TDM_DAI_MAX_SLOTS 8
struct bf5xx_tdm_port {
	u16 tcr1;
	u16 rcr1;
	u16 tcr2;
	u16 rcr2;
	unsigned int tx_map[BFIN_TDM_DAI_MAX_SLOTS];
	unsigned int rx_map[BFIN_TDM_DAI_MAX_SLOTS];
	int configured;
};

#endif
