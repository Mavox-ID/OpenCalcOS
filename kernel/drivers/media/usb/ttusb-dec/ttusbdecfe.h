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
#ifndef TTUSBDECFE_H
#define TTUSBDECFE_H

#include <beep/dvb/frontend.h>

struct ttusbdecfe_config
{
	int (*send_command)(struct dvb_frontend* fe, const u8 command,
			    int param_length, const u8 params[],
			    int *result_length, u8 cmd_result[]);
};

extern struct dvb_frontend* ttusbdecfe_dvbs_attach(const struct ttusbdecfe_config* config);

extern struct dvb_frontend* ttusbdecfe_dvbt_attach(const struct ttusbdecfe_config* config);

#endif // TTUSBDECFE_H
