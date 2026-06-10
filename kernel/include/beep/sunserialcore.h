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
#ifndef _SERIAL_SUN_H
#define _SERIAL_SUN_H

/* Serial keyboard defines for L1-A processing... */
#define SUNKBD_RESET		0xff
#define SUNKBD_L1		0x01
#define SUNKBD_UP		0x80
#define SUNKBD_A		0x4d

extern unsigned int suncore_mouse_baud_cflag_next(unsigned int, int *);
extern int suncore_mouse_baud_detection(unsigned char, int);

extern int sunserial_register_minors(struct uart_driver *, int);
extern void sunserial_unregister_minors(struct uart_driver *, int);

extern int sunserial_console_match(struct console *, struct device_node *,
				   struct uart_driver *, int, bool);
extern void sunserial_console_termios(struct console *,
				      struct device_node *);

#endif /* !(_SERIAL_SUN_H) */
