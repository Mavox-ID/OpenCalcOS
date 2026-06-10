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
#include <beep/regmap.h>
#include <beep/spi/spi.h>
#include <beep/init.h>
#include <beep/module.h>

static int regmap_spi_write(void *context, const void *data, size_t count)
{
	struct device *dev = context;
	struct spi_device *spi = to_spi_device(dev);

	return spi_write(spi, data, count);
}

static int regmap_spi_gather_write(void *context,
				   const void *reg, size_t reg_len,
				   const void *val, size_t val_len)
{
	struct device *dev = context;
	struct spi_device *spi = to_spi_device(dev);
	struct spi_message m;
	struct spi_transfer t[2] = { { .tx_buf = reg, .len = reg_len, },
				     { .tx_buf = val, .len = val_len, }, };

	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);

	return spi_sync(spi, &m);
}

static int regmap_spi_read(void *context,
			   const void *reg, size_t reg_size,
			   void *val, size_t val_size)
{
	struct device *dev = context;
	struct spi_device *spi = to_spi_device(dev);

	return spi_write_then_read(spi, reg, reg_size, val, val_size);
}

static struct regmap_bus regmap_spi = {
	.write = regmap_spi_write,
	.gather_write = regmap_spi_gather_write,
	.read = regmap_spi_read,
	.read_flag_mask = 0x80,
};

/**
 * regmap_init_spi(): Initialise register map
 *
 * @spi: Device that will be interacted with
 * @config: Configuration for register map
 *
 * The return value will be an ERR_PTR() on error or a valid pointer to
 * a struct regmap.
 */
struct regmap *regmap_init_spi(struct spi_device *spi,
			       const struct regmap_config *config)
{
	return regmap_init(&spi->dev, &regmap_spi, &spi->dev, config);
}
EXPORT_SYMBOL_GPL(regmap_init_spi);

/**
 * devm_regmap_init_spi(): Initialise register map
 *
 * @spi: Device that will be interacted with
 * @config: Configuration for register map
 *
 * The return value will be an ERR_PTR() on error or a valid pointer
 * to a struct regmap.  The map will be automatically freed by the
 * device management code.
 */
struct regmap *devm_regmap_init_spi(struct spi_device *spi,
				    const struct regmap_config *config)
{
	return devm_regmap_init(&spi->dev, &regmap_spi, &spi->dev, config);
}
EXPORT_SYMBOL_GPL(devm_regmap_init_spi);

MODULE_LICENSE("GPL");
