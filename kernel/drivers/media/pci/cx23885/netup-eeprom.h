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
#ifndef NETUP_EEPROM_H
#define NETUP_EEPROM_H

struct netup_port_info {
	u8 mac[6];/* card MAC address */
};

struct netup_card_info {
	struct netup_port_info port[2];/* ports - 1,2 */
	u8 rev;/* card revision */
};

extern int netup_eeprom_read(struct i2c_adapter *i2c_adap, u8 addr);
extern int netup_eeprom_write(struct i2c_adapter *i2c_adap, u8 addr, u8 data);
extern void netup_get_card_info(struct i2c_adapter *i2c_adap,
				struct netup_card_info *cinfo);

#endif
