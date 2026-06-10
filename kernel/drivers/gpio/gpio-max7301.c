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
#include <beep/module.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/mutex.h>
#include <beep/slab.h>
#include <beep/spi/spi.h>
#include <beep/spi/max7301.h>

/* A write to the MAX7301 means one message with one transfer */
static int max7301_spi_write(struct device *dev, unsigned int reg,
				unsigned int val)
{
	struct spi_device *spi = to_spi_device(dev);
	u16 word = ((reg & 0x7F) << 8) | (val & 0xFF);

	return spi_write(spi, (const u8 *)&word, sizeof(word));
}

/* A read from the MAX7301 means two transfers; here, one message each */

static int max7301_spi_read(struct device *dev, unsigned int reg)
{
	int ret;
	u16 word;
	struct spi_device *spi = to_spi_device(dev);

	word = 0x8000 | (reg << 8);
	ret = spi_write(spi, (const u8 *)&word, sizeof(word));
	if (ret)
		return ret;
	/*
	 * This relies on the fact, that a transfer with NULL tx_buf shifts out
	 * zero bytes (=NOOP for MAX7301)
	 */
	ret = spi_read(spi, (u8 *)&word, sizeof(word));
	if (ret)
		return ret;
	return word & 0xff;
}

static int max7301_probe(struct spi_device *spi)
{
	struct max7301 *ts;
	int ret;

	/* bits_per_word cannot be configured in platform data */
	spi->bits_per_word = 16;
	ret = spi_setup(spi);
	if (ret < 0)
		return ret;

	ts = kzalloc(sizeof(struct max7301), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	ts->read = max7301_spi_read;
	ts->write = max7301_spi_write;
	ts->dev = &spi->dev;

	ret = __max730x_probe(ts);
	if (ret)
		kfree(ts);
	return ret;
}

static int max7301_remove(struct spi_device *spi)
{
	return __max730x_remove(&spi->dev);
}

static const struct spi_device_id max7301_id[] = {
	{ "max7301", 0 },
	{ }
};
MODULE_DEVICE_TABLE(spi, max7301_id);

static struct spi_driver max7301_driver = {
	.driver = {
		.name = "max7301",
		.owner = THIS_MODULE,
	},
	.probe = max7301_probe,
	.remove = max7301_remove,
	.id_table = max7301_id,
};

static int __init max7301_init(void)
{
	return spi_register_driver(&max7301_driver);
}
/* register after spi postcore initcall and before
 * subsys initcalls that may rely on these GPIOs
 */
subsys_initcall(max7301_init);

static void __exit max7301_exit(void)
{
	spi_unregister_driver(&max7301_driver);
}
module_exit(max7301_exit);

MODULE_AUTHOR("Juergen Beisert, Wolfram Sang");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MAX7301 GPIO-Expander");
