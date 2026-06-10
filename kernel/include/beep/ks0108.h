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
#ifndef _KS0108_H_
#define _KS0108_H_

/* Write a byte to the data port */
extern void ks0108_writedata(unsigned char byte);

/* Write a byte to the control port */
extern void ks0108_writecontrol(unsigned char byte);

/* Set the controller's current display state (0..1) */
extern void ks0108_displaystate(unsigned char state);

/* Set the controller's current startline (0..63) */
extern void ks0108_startline(unsigned char startline);

/* Set the controller's current address (0..63) */
extern void ks0108_address(unsigned char address);

/* Set the controller's current page (0..7) */
extern void ks0108_page(unsigned char page);

/* Is the module inited? */
extern unsigned char ks0108_isinited(void);

#endif /* _KS0108_H_ */
