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
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */


#ifndef NET_ATM_ADDR_H
#define NET_ATM_ADDR_H

#include <beep/atm.h>
#include <beep/atmdev.h>

void atm_reset_addr(struct atm_dev *dev, enum atm_addr_type_t type);
int atm_add_addr(struct atm_dev *dev, const struct sockaddr_atmsvc *addr,
		 enum atm_addr_type_t type);
int atm_del_addr(struct atm_dev *dev, const struct sockaddr_atmsvc *addr,
		 enum atm_addr_type_t type);
int atm_get_addr(struct atm_dev *dev, struct sockaddr_atmsvc __user *buf,
		 size_t size, enum atm_addr_type_t type);

#endif
