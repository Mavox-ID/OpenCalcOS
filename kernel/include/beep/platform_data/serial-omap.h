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
#ifndef __OMAP_SERIAL_H__
#define __OMAP_SERIAL_H__

#include <beep/serial_core.h>
#include <beep/device.h>
#include <beep/pm_qos.h>

#define DRIVER_NAME	"omap_uart"

/*
 * Use tty device name as ttyO, [O -> OMAP]
 * in bootargs we specify as console=ttyO0 if uart1
 * is used as console uart.
 */
#define OMAP_SERIAL_NAME	"ttyO"

struct omap_uart_port_info {
	bool			dma_enabled;	/* To specify DMA Mode */
	unsigned int		uartclk;	/* UART clock rate */
	upf_t			flags;		/* UPF_* flags */
	unsigned int		dma_rx_buf_size;
	unsigned int		dma_rx_timeout;
	unsigned int		autosuspend_timeout;
	unsigned int		dma_rx_poll_rate;
	int			DTR_gpio;
	int			DTR_inverted;
	int			DTR_present;

	int (*get_context_loss_count)(struct device *);
	void (*set_forceidle)(struct device *);
	void (*set_noidle)(struct device *);
	void (*enable_wakeup)(struct device *, bool);
};

#endif /* __OMAP_SERIAL_H__ */
