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
#include <beep/kernel.h>
#include <beep/platform_device.h>
#include <beep/hw_random.h>
#include <beep/io.h>
#include <beep/timeriomem-rng.h>
#include <beep/jiffies.h>
#include <beep/sched.h>
#include <beep/timer.h>
#include <beep/completion.h>

static struct timeriomem_rng_data *timeriomem_rng_data;

static void timeriomem_rng_trigger(unsigned long);
static DEFINE_TIMER(timeriomem_rng_timer, timeriomem_rng_trigger, 0, 0);

/*
 * have data return 1, however return 0 if we have nothing
 */
static int timeriomem_rng_data_present(struct hwrng *rng, int wait)
{
	if (rng->priv == 0)
		return 1;

	if (!wait || timeriomem_rng_data->present)
		return timeriomem_rng_data->present;

	wait_for_completion(&timeriomem_rng_data->completion);

	return 1;
}

static int timeriomem_rng_data_read(struct hwrng *rng, u32 *data)
{
	unsigned long cur;
	s32 delay;

	*data = readl(timeriomem_rng_data->address);

	if (rng->priv != 0) {
		cur = jiffies;

		delay = cur - timeriomem_rng_timer.expires;
		delay = rng->priv - (delay % rng->priv);

		timeriomem_rng_timer.expires = cur + delay;
		timeriomem_rng_data->present = 0;

		init_completion(&timeriomem_rng_data->completion);
		add_timer(&timeriomem_rng_timer);
	}

	return 4;
}

static void timeriomem_rng_trigger(unsigned long dummy)
{
	timeriomem_rng_data->present = 1;
	complete(&timeriomem_rng_data->completion);
}

static struct hwrng timeriomem_rng_ops = {
	.name		= "timeriomem",
	.data_present	= timeriomem_rng_data_present,
	.data_read	= timeriomem_rng_data_read,
	.priv		= 0,
};

static int timeriomem_rng_probe(struct platform_device *pdev)
{
	struct resource *res;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	if (!res)
		return -ENOENT;

	timeriomem_rng_data = pdev->dev.platform_data;

	timeriomem_rng_data->address = ioremap(res->start, resource_size(res));
	if (!timeriomem_rng_data->address)
		return -EIO;

	if (timeriomem_rng_data->period != 0
		&& usecs_to_jiffies(timeriomem_rng_data->period) > 0) {
		timeriomem_rng_timer.expires = jiffies;

		timeriomem_rng_ops.priv = usecs_to_jiffies(
						timeriomem_rng_data->period);
	}
	timeriomem_rng_data->present = 1;

	ret = hwrng_register(&timeriomem_rng_ops);
	if (ret)
		goto failed;

	dev_info(&pdev->dev, "32bits from 0x%p @ %dus\n",
			timeriomem_rng_data->address,
			timeriomem_rng_data->period);

	return 0;

failed:
	dev_err(&pdev->dev, "problem registering\n");
	iounmap(timeriomem_rng_data->address);

	return ret;
}

static int timeriomem_rng_remove(struct platform_device *pdev)
{
	del_timer_sync(&timeriomem_rng_timer);
	hwrng_unregister(&timeriomem_rng_ops);

	iounmap(timeriomem_rng_data->address);

	return 0;
}

static struct platform_driver timeriomem_rng_driver = {
	.driver = {
		.name		= "timeriomem_rng",
		.owner		= THIS_MODULE,
	},
	.probe		= timeriomem_rng_probe,
	.remove		= timeriomem_rng_remove,
};

module_platform_driver(timeriomem_rng_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Clouter <alex@digriz.org.uk>");
MODULE_DESCRIPTION("Timer IOMEM H/W RNG driver");
