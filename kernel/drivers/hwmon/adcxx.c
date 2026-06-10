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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/slab.h>
#include <beep/device.h>
#include <beep/err.h>
#include <beep/sysfs.h>
#include <beep/hwmon.h>
#include <beep/hwmon-sysfs.h>
#include <beep/mutex.h>
#include <beep/mod_devicetable.h>
#include <beep/spi/spi.h>

#define DRVNAME		"adcxx"

struct adcxx {
	struct device *hwmon_dev;
	struct mutex lock;
	u32 channels;
	u32 reference; /* in millivolts */
};

/* sysfs hook function */
static ssize_t adcxx_read(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	struct spi_device *spi = to_spi_device(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adcxx *adc = spi_get_drvdata(spi);
	u8 tx_buf[2];
	u8 rx_buf[2];
	int status;
	u32 value;

	if (mutex_lock_interruptible(&adc->lock))
		return -ERESTARTSYS;

	if (adc->channels == 1) {
		status = spi_read(spi, rx_buf, sizeof(rx_buf));
	} else {
		tx_buf[0] = attr->index << 3; /* other bits are don't care */
		status = spi_write_then_read(spi, tx_buf, sizeof(tx_buf),
						rx_buf, sizeof(rx_buf));
	}
	if (status < 0) {
		dev_warn(dev, "SPI synch. transfer failed with status %d\n",
				status);
		goto out;
	}

	value = (rx_buf[0] << 8) + rx_buf[1];
	dev_dbg(dev, "raw value = 0x%x\n", value);

	value = value * adc->reference >> 12;
	status = sprintf(buf, "%d\n", value);
out:
	mutex_unlock(&adc->lock);
	return status;
}

static ssize_t adcxx_show_min(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	/* The minimum reference is 0 for this chip family */
	return sprintf(buf, "0\n");
}

static ssize_t adcxx_show_max(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	struct spi_device *spi = to_spi_device(dev);
	struct adcxx *adc = spi_get_drvdata(spi);
	u32 reference;

	if (mutex_lock_interruptible(&adc->lock))
		return -ERESTARTSYS;

	reference = adc->reference;

	mutex_unlock(&adc->lock);

	return sprintf(buf, "%d\n", reference);
}

static ssize_t adcxx_set_max(struct device *dev,
	struct device_attribute *devattr, const char *buf, size_t count)
{
	struct spi_device *spi = to_spi_device(dev);
	struct adcxx *adc = spi_get_drvdata(spi);
	unsigned long value;

	if (kstrtoul(buf, 10, &value))
		return -EINVAL;

	if (mutex_lock_interruptible(&adc->lock))
		return -ERESTARTSYS;

	adc->reference = value;

	mutex_unlock(&adc->lock);

	return count;
}

static ssize_t adcxx_show_name(struct device *dev, struct device_attribute
			      *devattr, char *buf)
{
	return sprintf(buf, "%s\n", to_spi_device(dev)->modalias);
}

static struct sensor_device_attribute ad_input[] = {
	SENSOR_ATTR(name, S_IRUGO, adcxx_show_name, NULL, 0),
	SENSOR_ATTR(in_min, S_IRUGO, adcxx_show_min, NULL, 0),
	SENSOR_ATTR(in_max, S_IWUSR | S_IRUGO, adcxx_show_max,
					adcxx_set_max, 0),
	SENSOR_ATTR(in0_input, S_IRUGO, adcxx_read, NULL, 0),
	SENSOR_ATTR(in1_input, S_IRUGO, adcxx_read, NULL, 1),
	SENSOR_ATTR(in2_input, S_IRUGO, adcxx_read, NULL, 2),
	SENSOR_ATTR(in3_input, S_IRUGO, adcxx_read, NULL, 3),
	SENSOR_ATTR(in4_input, S_IRUGO, adcxx_read, NULL, 4),
	SENSOR_ATTR(in5_input, S_IRUGO, adcxx_read, NULL, 5),
	SENSOR_ATTR(in6_input, S_IRUGO, adcxx_read, NULL, 6),
	SENSOR_ATTR(in7_input, S_IRUGO, adcxx_read, NULL, 7),
};

/*----------------------------------------------------------------------*/

static int adcxx_probe(struct spi_device *spi)
{
	int channels = spi_get_device_id(spi)->driver_data;
	struct adcxx *adc;
	int status;
	int i;

	adc = devm_kzalloc(&spi->dev, sizeof(*adc), GFP_KERNEL);
	if (!adc)
		return -ENOMEM;

	/* set a default value for the reference */
	adc->reference = 3300;
	adc->channels = channels;
	mutex_init(&adc->lock);

	mutex_lock(&adc->lock);

	spi_set_drvdata(spi, adc);

	for (i = 0; i < 3 + adc->channels; i++) {
		status = device_create_file(&spi->dev, &ad_input[i].dev_attr);
		if (status) {
			dev_err(&spi->dev, "device_create_file failed.\n");
			goto out_err;
		}
	}

	adc->hwmon_dev = hwmon_device_register(&spi->dev);
	if (IS_ERR(adc->hwmon_dev)) {
		dev_err(&spi->dev, "hwmon_device_register failed.\n");
		status = PTR_ERR(adc->hwmon_dev);
		goto out_err;
	}

	mutex_unlock(&adc->lock);
	return 0;

out_err:
	for (i--; i >= 0; i--)
		device_remove_file(&spi->dev, &ad_input[i].dev_attr);

	spi_set_drvdata(spi, NULL);
	mutex_unlock(&adc->lock);
	return status;
}

static int adcxx_remove(struct spi_device *spi)
{
	struct adcxx *adc = spi_get_drvdata(spi);
	int i;

	mutex_lock(&adc->lock);
	hwmon_device_unregister(adc->hwmon_dev);
	for (i = 0; i < 3 + adc->channels; i++)
		device_remove_file(&spi->dev, &ad_input[i].dev_attr);

	spi_set_drvdata(spi, NULL);
	mutex_unlock(&adc->lock);

	return 0;
}

static const struct spi_device_id adcxx_ids[] = {
	{ "adcxx1s", 1 },
	{ "adcxx2s", 2 },
	{ "adcxx4s", 4 },
	{ "adcxx8s", 8 },
	{ },
};
MODULE_DEVICE_TABLE(spi, adcxx_ids);

static struct spi_driver adcxx_driver = {
	.driver = {
		.name	= "adcxx",
		.owner	= THIS_MODULE,
	},
	.id_table = adcxx_ids,
	.probe	= adcxx_probe,
	.remove	= adcxx_remove,
};

module_spi_driver(adcxx_driver);

MODULE_AUTHOR("Marc Pignat");
MODULE_DESCRIPTION("National Semiconductor adcxx8sxxx Beep driver");
MODULE_LICENSE("GPL");
