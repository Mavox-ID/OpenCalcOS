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
#ifndef __I2C_PNX_H__
#define __I2C_PNX_H__

struct platform_device;
struct clk;

struct i2c_pnx_mif {
	int			ret;		/* Return value */
	int			mode;		/* Interface mode */
	struct completion	complete;	/* I/O completion */
	struct timer_list	timer;		/* Timeout */
	u8 *			buf;		/* Data buffer */
	int			len;		/* Length of data buffer */
	int			order;		/* RX Bytes to order via TX */
};

struct i2c_pnx_algo_data {
	void __iomem		*ioaddr;
	struct i2c_pnx_mif	mif;
	int			last;
	struct clk		*clk;
	struct i2c_adapter	adapter;
	phys_addr_t		base;
	int			irq;
	u32			timeout;
};

#endif /* __I2C_PNX_H__ */
