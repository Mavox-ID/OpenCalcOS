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
#include "devices/devices-common.h"

extern const struct imx_imx_fb_data imx1_imx_fb_data;
#define imx1_add_imx_fb(pdata) \
    imx_add_imx_fb(&imx1_imx_fb_data, pdata)

extern const struct imx_imx_i2c_data imx1_imx_i2c_data;
#define imx1_add_imx_i2c(pdata)		\
	imx_add_imx_i2c(&imx1_imx_i2c_data, pdata)

extern const struct imx_imx_uart_3irq_data imx1_imx_uart_data[];
#define imx1_add_imx_uart(id, pdata)	\
	imx_add_imx_uart_3irq(&imx1_imx_uart_data[id], pdata)
#define imx1_add_imx_uart0(pdata)	imx1_add_imx_uart(0, pdata)
#define imx1_add_imx_uart1(pdata)	imx1_add_imx_uart(1, pdata)

extern const struct imx_spi_imx_data imx1_cspi_data[];
#define imx1_add_cspi(id, pdata)   \
	imx_add_spi_imx(&imx1_cspi_data[id], pdata)

#define imx1_add_spi_imx0(pdata) imx1_add_cspi(0, pdata)
#define imx1_add_spi_imx1(pdata) imx1_add_cspi(1, pdata)
