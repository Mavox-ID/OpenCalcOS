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
#include "includes.h"
#include "hardware.h"
#include "message.h"
#include "card.h"

#ifdef DEBUG
static char *events[] = { "ISDN_STAT_STAVAIL",
			  "ISDN_STAT_ICALL",
			  "ISDN_STAT_RUN",
			  "ISDN_STAT_STOP",
			  "ISDN_STAT_DCONN",
			  "ISDN_STAT_BCONN",
			  "ISDN_STAT_DHUP",
			  "ISDN_STAT_BHUP",
			  "ISDN_STAT_CINF",
			  "ISDN_STAT_LOAD",
			  "ISDN_STAT_UNLOAD",
			  "ISDN_STAT_BSENT",
			  "ISDN_STAT_NODCH",
			  "ISDN_STAT_ADDCH",
			  "ISDN_STAT_CAUSE" };
#endif

int indicate_status(int card, int event, ulong Channel, char *Data)
{
	isdn_ctrl cmd;

#ifdef DEBUG
	pr_debug("%s: Indicating event %s on Channel %d\n",
		 sc_adapter[card]->devicename, events[event - 256], Channel);
#endif
	if (Data != NULL) {
		pr_debug("%s: Event data: %s\n", sc_adapter[card]->devicename,
			 Data);
		switch (event) {
		case ISDN_STAT_BSENT:
			memcpy(&cmd.parm.length, Data, sizeof(cmd.parm.length));
			break;
		case ISDN_STAT_ICALL:
			memcpy(&cmd.parm.setup, Data, sizeof(cmd.parm.setup));
			break;
		default:
			strcpy(cmd.parm.num, Data);
		}
	}

	cmd.command = event;
	cmd.driver = sc_adapter[card]->driverId;
	cmd.arg = Channel;
	return sc_adapter[card]->card->statcallb(&cmd);
}
