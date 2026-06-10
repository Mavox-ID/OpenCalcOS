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
#include <beep/leds.h>
#include <beep/module.h>
#include <beep/mutex.h>
#include <beep/slab.h>
#include <beep/spinlock.h>
#include <beep/workqueue.h>
#include <beep/spi/spi.h>

struct dac124s085_led {
	struct led_classdev	ldev;
	struct spi_device	*spi;
	int			id;
	int			brightness;
	char			name[sizeof("dac124s085-3")];

	struct mutex		mutex;
	struct work_struct	work;
	spinlock_t		lock;
};

struct dac124s085 {
	struct dac124s085_led leds[4];
};

#define REG_WRITE		(0 << 12)
#define REG_WRITE_UPDATE	(1 << 12)
#define ALL_WRITE_UPDATE	(2 << 12)
#define POWER_DOWN_OUTPUT	(3 << 12)

static void dac124s085_led_work(struct work_struct *work)
{
	struct dac124s085_led *led = container_of(work, struct dac124s085_led,
						  work);
	u16 word;

	mutex_lock(&led->mutex);
	word = cpu_to_le16(((led->id) << 14) | REG_WRITE_UPDATE |
			   (led->brightness & 0xfff));
	spi_write(led->spi, (const u8 *)&word, sizeof(word));
	mutex_unlock(&led->mutex);
}

static void dac124s085_set_brightness(struct led_classdev *ldev,
				      enum led_brightness brightness)
{
	struct dac124s085_led *led = container_of(ldev, struct dac124s085_led,
						  ldev);

	spin_lock(&led->lock);
	led->brightness = brightness;
	schedule_work(&led->work);
	spin_unlock(&led->lock);
}

static int dac124s085_probe(struct spi_device *spi)
{
	struct dac124s085	*dac;
	struct dac124s085_led	*led;
	int i, ret;

	dac = devm_kzalloc(&spi->dev, sizeof(*dac), GFP_KERNEL);
	if (!dac)
		return -ENOMEM;

	spi->bits_per_word = 16;

	for (i = 0; i < ARRAY_SIZE(dac->leds); i++) {
		led		= dac->leds + i;
		led->id		= i;
		led->brightness	= LED_OFF;
		led->spi	= spi;
		snprintf(led->name, sizeof(led->name), "dac124s085-%d", i);
		spin_lock_init(&led->lock);
		INIT_WORK(&led->work, dac124s085_led_work);
		mutex_init(&led->mutex);
		led->ldev.name = led->name;
		led->ldev.brightness = LED_OFF;
		led->ldev.max_brightness = 0xfff;
		led->ldev.brightness_set = dac124s085_set_brightness;
		ret = led_classdev_register(&spi->dev, &led->ldev);
		if (ret < 0)
			goto eledcr;
	}

	spi_set_drvdata(spi, dac);

	return 0;

eledcr:
	while (i--)
		led_classdev_unregister(&dac->leds[i].ldev);

	spi_set_drvdata(spi, NULL);
	return ret;
}

static int dac124s085_remove(struct spi_device *spi)
{
	struct dac124s085	*dac = spi_get_drvdata(spi);
	int i;

	for (i = 0; i < ARRAY_SIZE(dac->leds); i++) {
		led_classdev_unregister(&dac->leds[i].ldev);
		cancel_work_sync(&dac->leds[i].work);
	}

	spi_set_drvdata(spi, NULL);

	return 0;
}

static struct spi_driver dac124s085_driver = {
	.probe		= dac124s085_probe,
	.remove		= dac124s085_remove,
	.driver = {
		.name	= "dac124s085",
		.owner	= THIS_MODULE,
	},
};

module_spi_driver(dac124s085_driver);

MODULE_AUTHOR("Guennadi Liakhovetski <lg@denx.de>");
MODULE_DESCRIPTION("DAC124S085 LED driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:dac124s085");
