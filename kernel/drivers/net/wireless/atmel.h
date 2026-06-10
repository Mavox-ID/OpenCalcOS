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
#ifndef _ATMEL_H
#define _ATMEL_H

typedef enum {
	ATMEL_FW_TYPE_NONE = 0,
	ATMEL_FW_TYPE_502,
	ATMEL_FW_TYPE_502D,
	ATMEL_FW_TYPE_502E,
	ATMEL_FW_TYPE_502_3COM,
	ATMEL_FW_TYPE_504,
	ATMEL_FW_TYPE_504_2958,
	ATMEL_FW_TYPE_504A_2958,
	ATMEL_FW_TYPE_506
} AtmelFWType;

struct net_device *init_atmel_card(unsigned short, unsigned long, const AtmelFWType, struct device *, 
				    int (*present_func)(void *), void * );
void stop_atmel_card( struct net_device *);
int atmel_open( struct net_device * );

#endif
