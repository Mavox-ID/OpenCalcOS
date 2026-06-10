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
#include <beep/spi/spi.h>
#include <beep/types.h>
#include <beep/err.h>

#include <beep/iio/iio.h>
#include "ad7606.h"

#define MAX_SPI_FREQ_HZ		23500000	/* VDRIVE above 4.75 V */

static int ad7606_spi_read_block(struct device *dev,
				 int count, void *buf)
{
	struct spi_device *spi = to_spi_device(dev);
	int i, ret;
	unsigned short *data = buf;

	ret = spi_read(spi, (u8 *)buf, count * 2);
	if (ret < 0) {
		dev_err(&spi->dev, "SPI read error\n");
		return ret;
	}

	for (i = 0; i < count; i++)
		data[i] = be16_to_cpu(data[i]);

	return 0;
}

static const struct ad7606_bus_ops ad7606_spi_bops = {
	.read_block	= ad7606_spi_read_block,
};

static int ad7606_spi_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;

	indio_dev = ad7606_probe(&spi->dev, spi->irq, NULL,
			   spi_get_device_id(spi)->driver_data,
			   &ad7606_spi_bops);

	if (IS_ERR(indio_dev))
		return PTR_ERR(indio_dev);

	spi_set_drvdata(spi, indio_dev);

	return 0;
}

static int ad7606_spi_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = dev_get_drvdata(&spi->dev);

	return ad7606_remove(indio_dev, spi->irq);
}

#ifdef CONFIG_PM
static int ad7606_spi_suspend(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);

	ad7606_suspend(indio_dev);

	return 0;
}

static int ad7606_spi_resume(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);

	ad7606_resume(indio_dev);

	return 0;
}

static const struct dev_pm_ops ad7606_pm_ops = {
	.suspend = ad7606_spi_suspend,
	.resume  = ad7606_spi_resume,
};
#define AD7606_SPI_PM_OPS (&ad7606_pm_ops)

#else
#define AD7606_SPI_PM_OPS NULL
#endif

static const struct spi_device_id ad7606_id[] = {
	{"ad7606-8", ID_AD7606_8},
	{"ad7606-6", ID_AD7606_6},
	{"ad7606-4", ID_AD7606_4},
	{}
};
MODULE_DEVICE_TABLE(spi, ad7606_id);

static struct spi_driver ad7606_driver = {
	.driver = {
		.name = "ad7606",
		.owner = THIS_MODULE,
		.pm    = AD7606_SPI_PM_OPS,
	},
	.probe = ad7606_spi_probe,
	.remove = ad7606_spi_remove,
	.id_table = ad7606_id,
};
module_spi_driver(ad7606_driver);

MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.ucbeep.org>");
MODULE_DESCRIPTION("Analog Devices AD7606 ADC");
MODULE_LICENSE("GPL v2");
