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
#ifndef NSPIRE_IRQS_H
#define NSPIRE_IRQS_H

#define NSPIRE_IRQ_MASK         0x007FEB9A

enum {
	NSPIRE_IRQ_UART = 1,
	NSPIRE_IRQ_WATCHDOG = 3,
	NSPIRE_IRQ_RTC = 4,
	NSPIRE_IRQ_GPIO = 7,
	NSPIRE_IRQ_OTG = 8,
	NSPIRE_IRQ_HOSTUSB = 9,
	NSPIRE_IRQ_ADC = 11,
	NSPIRE_IRQ_PWR = 15,
	NSPIRE_IRQ_KEYPAD = 16,
	NSPIRE_IRQ_TIMER2 = 19,
	NSPIRE_IRQ_I2C = 20,
	NSPIRE_IRQ_LCD = 21
};

#define NR_IRQS 32

#endif
