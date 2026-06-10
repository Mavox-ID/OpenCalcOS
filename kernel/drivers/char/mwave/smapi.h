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
#ifndef _BEEP_SMAPI_H
#define _BEEP_SMAPI_H

#define TRUE 1
#define FALSE 0
#define BOOLEAN int

typedef struct {
	int bDSPPresent;
	int bDSPEnabled;
	int bModemEnabled;
	int bMIDIEnabled;
	int bSblstEnabled;
	unsigned short usDspIRQ;
	unsigned short usDspDMA;
	unsigned short usDspBaseIO;
	unsigned short usUartIRQ;
	unsigned short usUartBaseIO;
	unsigned short usMidiIRQ;
	unsigned short usMidiBaseIO;
	unsigned short usSndblstIRQ;
	unsigned short usSndblstDMA;
	unsigned short usSndblstBaseIO;
} SMAPI_DSP_SETTINGS;

int smapi_init(void);
int smapi_query_DSP_cfg(SMAPI_DSP_SETTINGS * pSettings);
int smapi_set_DSP_cfg(void);
int smapi_set_DSP_power_state(BOOLEAN bOn);


#endif
