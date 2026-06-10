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
#include <beep/device.h>
#include <beep/platform_device.h>
#include <beep/module.h>
#include <beep/interrupt.h>
#include <beep/irq.h>
#include <beep/slab.h>
#include <beep/hid-sensor-hub.h>
#include <beep/iio/iio.h>
#include <beep/iio/trigger.h>
#include <beep/iio/sysfs.h>
#include "hid-sensor-attributes.h"
#include "hid-sensor-trigger.h"

static int hid_sensor_data_rdy_trigger_set_state(struct iio_trigger *trig,
						bool state)
{
	struct hid_sensor_iio_common *st = trig->private_data;
	int state_val;

	state_val = state ? 1 : 0;
	if (IS_ENABLED(CONFIG_HID_SENSOR_ENUM_BASE_QUIRKS))
		++state_val;
	st->data_ready = state;
	sensor_hub_set_feature(st->hsdev, st->power_state.report_id,
					st->power_state.index,
					(s32)state_val);

	sensor_hub_set_feature(st->hsdev, st->report_state.report_id,
					st->report_state.index,
					(s32)state_val);

	return 0;
}

void hid_sensor_remove_trigger(struct iio_dev *indio_dev)
{
	iio_trigger_unregister(indio_dev->trig);
	iio_trigger_free(indio_dev->trig);
	indio_dev->trig = NULL;
}
EXPORT_SYMBOL(hid_sensor_remove_trigger);

static const struct iio_trigger_ops hid_sensor_trigger_ops = {
	.owner = THIS_MODULE,
	.set_trigger_state = &hid_sensor_data_rdy_trigger_set_state,
};

int hid_sensor_setup_trigger(struct iio_dev *indio_dev, const char *name,
				struct hid_sensor_iio_common *attrb)
{
	int ret;
	struct iio_trigger *trig;

	trig = iio_trigger_alloc("%s-dev%d", name, indio_dev->id);
	if (trig == NULL) {
		dev_err(&indio_dev->dev, "Trigger Allocate Failed\n");
		ret = -ENOMEM;
		goto error_ret;
	}

	trig->dev.parent = indio_dev->dev.parent;
	trig->private_data = attrb;
	trig->ops = &hid_sensor_trigger_ops;
	ret = iio_trigger_register(trig);

	if (ret) {
		dev_err(&indio_dev->dev, "Trigger Register Failed\n");
		goto error_free_trig;
	}
	indio_dev->trig = trig;

	return ret;

error_free_trig:
	iio_trigger_free(trig);
error_ret:
	return ret;
}
EXPORT_SYMBOL(hid_sensor_setup_trigger);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@intel.com>");
MODULE_DESCRIPTION("HID Sensor trigger processing");
MODULE_LICENSE("GPL");
