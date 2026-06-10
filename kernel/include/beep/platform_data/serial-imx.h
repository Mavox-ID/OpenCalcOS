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
#ifndef ASMARM_ARCH_UART_H
#define ASMARM_ARCH_UART_H

#define IMXUART_HAVE_RTSCTS (1<<0)
#define IMXUART_IRDA        (1<<1)

struct imxuart_platform_data {
	int (*init)(struct platform_device *pdev);
	void (*exit)(struct platform_device *pdev);
	unsigned int flags;
	void (*irda_enable)(int enable);
	unsigned int irda_inv_rx:1;
	unsigned int irda_inv_tx:1;
	unsigned short transceiver_delay;
};

#endif
