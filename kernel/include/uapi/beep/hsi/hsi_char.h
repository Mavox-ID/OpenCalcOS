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
#ifndef __HSI_CHAR_H
#define __HSI_CHAR_H

#define HSI_CHAR_MAGIC		'k'
#define HSC_IOW(num, dtype)	_IOW(HSI_CHAR_MAGIC, num, dtype)
#define HSC_IOR(num, dtype)	_IOR(HSI_CHAR_MAGIC, num, dtype)
#define HSC_IOWR(num, dtype)	_IOWR(HSI_CHAR_MAGIC, num, dtype)
#define HSC_IO(num)		_IO(HSI_CHAR_MAGIC, num)

#define HSC_RESET		HSC_IO(16)
#define HSC_SET_PM		HSC_IO(17)
#define HSC_SEND_BREAK		HSC_IO(18)
#define HSC_SET_RX		HSC_IOW(19, struct hsc_rx_config)
#define HSC_GET_RX		HSC_IOW(20, struct hsc_rx_config)
#define HSC_SET_TX		HSC_IOW(21, struct hsc_tx_config)
#define HSC_GET_TX		HSC_IOW(22, struct hsc_tx_config)

#define HSC_PM_DISABLE		0
#define HSC_PM_ENABLE		1

#define HSC_MODE_STREAM		1
#define HSC_MODE_FRAME		2
#define HSC_FLOW_SYNC		0
#define HSC_ARB_RR		0
#define HSC_ARB_PRIO		1

struct hsc_rx_config {
	uint32_t mode;
	uint32_t flow;
	uint32_t channels;
};

struct hsc_tx_config {
	uint32_t mode;
	uint32_t channels;
	uint32_t speed;
	uint32_t arb_mode;
};

#endif /* __HSI_CHAR_H */
