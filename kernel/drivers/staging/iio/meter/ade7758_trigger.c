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
#include "ade7758.h"

/**
 * ade7758_data_rdy_trig_poll() the event handler for the data rdy trig
 **/
static irqreturn_t ade7758_data_rdy_trig_poll(int irq, void *private)
{
	disable_irq_nosync(irq);
	iio_trigger_poll(private, iio_get_time_ns());

	return IRQ_HANDLED;
}

/**
 * ade7758_data_rdy_trigger_set_state() set datardy interrupt state
 **/
static int ade7758_data_rdy_trigger_set_state(struct iio_trigger *trig,
						bool state)
{
	struct iio_dev *indio_dev = trig->private_data;

	dev_dbg(&indio_dev->dev, "%s (%d)\n", __func__, state);
	return ade7758_set_irq(&indio_dev->dev, state);
}

/**
 * ade7758_trig_try_reen() try renabling irq for data rdy trigger
 * @trig:	the datardy trigger
 **/
static int ade7758_trig_try_reen(struct iio_trigger *trig)
{
	struct iio_dev *indio_dev = trig->private_data;
	struct ade7758_state *st = iio_priv(indio_dev);

	enable_irq(st->us->irq);
	/* irq reenabled so success! */
	return 0;
}

static const struct iio_trigger_ops ade7758_trigger_ops = {
	.owner = THIS_MODULE,
	.set_trigger_state = &ade7758_data_rdy_trigger_set_state,
	.try_reenable = &ade7758_trig_try_reen,
};

int ade7758_probe_trigger(struct iio_dev *indio_dev)
{
	struct ade7758_state *st = iio_priv(indio_dev);
	int ret;

	st->trig = iio_trigger_alloc("%s-dev%d",
					spi_get_device_id(st->us)->name,
					indio_dev->id);
	if (st->trig == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}

	ret = request_irq(st->us->irq,
			  ade7758_data_rdy_trig_poll,
			  IRQF_TRIGGER_LOW,
			  spi_get_device_id(st->us)->name,
			  st->trig);
	if (ret)
		goto error_free_trig;

	st->trig->dev.parent = &st->us->dev;
	st->trig->ops = &ade7758_trigger_ops;
	st->trig->private_data = indio_dev;
	ret = iio_trigger_register(st->trig);

	/* select default trigger */
	indio_dev->trig = st->trig;
	if (ret)
		goto error_free_irq;

	return 0;

error_free_irq:
	free_irq(st->us->irq, st->trig);
error_free_trig:
	iio_trigger_free(st->trig);
error_ret:
	return ret;
}

void ade7758_remove_trigger(struct iio_dev *indio_dev)
{
	struct ade7758_state *st = iio_priv(indio_dev);

	iio_trigger_unregister(st->trig);
	free_irq(st->us->irq, st->trig);
	iio_trigger_free(st->trig);
}
