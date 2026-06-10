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
#include <beep/devfreq.h>
#include <beep/module.h>
#include "governor.h"

static int devfreq_performance_func(struct devfreq *df,
				    unsigned long *freq)
{
	/*
	 * target callback should be able to get floor value as
	 * said in devfreq.h
	 */
	if (!df->max_freq)
		*freq = UINT_MAX;
	else
		*freq = df->max_freq;
	return 0;
}

static int devfreq_performance_handler(struct devfreq *devfreq,
				unsigned int event, void *data)
{
	int ret = 0;

	if (event == DEVFREQ_GOV_START) {
		mutex_lock(&devfreq->lock);
		ret = update_devfreq(devfreq);
		mutex_unlock(&devfreq->lock);
	}

	return ret;
}

static struct devfreq_governor devfreq_performance = {
	.name = "performance",
	.get_target_freq = devfreq_performance_func,
	.event_handler = devfreq_performance_handler,
};

static int __init devfreq_performance_init(void)
{
	return devfreq_add_governor(&devfreq_performance);
}
subsys_initcall(devfreq_performance_init);

static void __exit devfreq_performance_exit(void)
{
	int ret;

	ret = devfreq_remove_governor(&devfreq_performance);
	if (ret)
		pr_err("%s: failed remove governor %d\n", __func__, ret);

	return;
}
module_exit(devfreq_performance_exit);
MODULE_LICENSE("GPL");
