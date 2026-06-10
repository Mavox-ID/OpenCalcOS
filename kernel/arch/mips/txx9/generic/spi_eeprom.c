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
#include <beep/init.h>
#include <beep/slab.h>
#include <beep/export.h>
#include <beep/device.h>
#include <beep/spi/spi.h>
#include <beep/spi/eeprom.h>
#include <asm/txx9/spi.h>

#define AT250X0_PAGE_SIZE	8

/* register board information for at25 driver */
int __init spi_eeprom_register(int busid, int chipid, int size)
{
	struct spi_board_info info = {
		.modalias = "at25",
		.max_speed_hz = 1500000,	/* 1.5Mbps */
		.bus_num = busid,
		.chip_select = chipid,
		/* Mode 0: High-Active, Sample-Then-Shift */
	};
	struct spi_eeprom *eeprom;
	eeprom = kzalloc(sizeof(*eeprom), GFP_KERNEL);
	if (!eeprom)
		return -ENOMEM;
	strcpy(eeprom->name, "at250x0");
	eeprom->byte_len = size;
	eeprom->page_size = AT250X0_PAGE_SIZE;
	eeprom->flags = EE_ADDR1;
	info.platform_data = eeprom;
	return spi_register_board_info(&info, 1);
}

/* simple temporary spi driver to provide early access to seeprom. */

static struct read_param {
	int busid;
	int chipid;
	int address;
	unsigned char *buf;
	int len;
} *read_param;

static int __init early_seeprom_probe(struct spi_device *spi)
{
	int stat = 0;
	u8 cmd[2];
	int len = read_param->len;
	char *buf = read_param->buf;
	int address = read_param->address;

	dev_info(&spi->dev, "spiclk %u KHz.\n",
		 (spi->max_speed_hz + 500) / 1000);
	if (read_param->busid != spi->master->bus_num ||
	    read_param->chipid != spi->chip_select)
		return -ENODEV;
	while (len > 0) {
		/* spi_write_then_read can only work with small chunk */
		int c = len < AT250X0_PAGE_SIZE ? len : AT250X0_PAGE_SIZE;
		cmd[0] = 0x03;	/* AT25_READ */
		cmd[1] = address;
		stat = spi_write_then_read(spi, cmd, sizeof(cmd), buf, c);
		buf += c;
		len -= c;
		address += c;
	}
	return stat;
}

static struct spi_driver early_seeprom_driver __initdata = {
	.driver = {
		.name	= "at25",
		.owner	= THIS_MODULE,
	},
	.probe	= early_seeprom_probe,
};

int __init spi_eeprom_read(int busid, int chipid, int address,
			   unsigned char *buf, int len)
{
	int ret;
	struct read_param param = {
		.busid = busid,
		.chipid = chipid,
		.address = address,
		.buf = buf,
		.len = len
	};

	read_param = &param;
	ret = spi_register_driver(&early_seeprom_driver);
	if (!ret)
		spi_unregister_driver(&early_seeprom_driver);
	return ret;
}
