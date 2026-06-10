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
#include <beep/interrupt.h>
#include <beep/kernel.h>
#include <beep/spi/spi.h>
#include <beep/export.h>

#include <beep/iio/iio.h>
#include <beep/iio/trigger.h>
#include <beep/iio/imu/adis.h>

static int adis_data_rdy_trigger_set_state(struct iio_trigger *trig,
						bool state)
{
	struct adis *adis = trig->private_data;

	return adis_enable_irq(adis, state);
}

static const struct iio_trigger_ops adis_trigger_ops = {
	.owner = THIS_MODULE,
	.set_trigger_state = &adis_data_rdy_trigger_set_state,
};

/**
 * adis_probe_trigger() - Sets up trigger for a adis device
 * @adis: The adis device
 * @indio_dev: The IIO device
 *
 * Returns 0 on success or a negative error code
 *
 * adis_remove_trigger() should be used to free the trigger.
 */
int adis_probe_trigger(struct adis *adis, struct iio_dev *indio_dev)
{
	int ret;

	adis->trig = iio_trigger_alloc("%s-dev%d", indio_dev->name,
					indio_dev->id);
	if (adis->trig == NULL)
		return -ENOMEM;

	ret = request_irq(adis->spi->irq,
			  &iio_trigger_generic_data_rdy_poll,
			  IRQF_TRIGGER_RISING,
			  indio_dev->name,
			  adis->trig);
	if (ret)
		goto error_free_trig;

	adis->trig->dev.parent = &adis->spi->dev;
	adis->trig->ops = &adis_trigger_ops;
	adis->trig->private_data = adis;
	ret = iio_trigger_register(adis->trig);

	indio_dev->trig = adis->trig;
	if (ret)
		goto error_free_irq;

	return 0;

error_free_irq:
	free_irq(adis->spi->irq, adis->trig);
error_free_trig:
	iio_trigger_free(adis->trig);
	return ret;
}
EXPORT_SYMBOL_GPL(adis_probe_trigger);

/**
 * adis_remove_trigger() - Remove trigger for a adis devices
 * @adis: The adis device
 *
 * Removes the trigger previously registered with adis_probe_trigger().
 */
void adis_remove_trigger(struct adis *adis)
{
	iio_trigger_unregister(adis->trig);
	free_irq(adis->spi->irq, adis->trig);
	iio_trigger_free(adis->trig);
}
EXPORT_SYMBOL_GPL(adis_remove_trigger);
