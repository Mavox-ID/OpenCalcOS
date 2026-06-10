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
#define KMSG_COMPONENT "sclp_config"
#define pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#include <beep/init.h>
#include <beep/errno.h>
#include <beep/cpu.h>
#include <beep/device.h>
#include <beep/workqueue.h>
#include <asm/smp.h>

#include "sclp.h"

struct conf_mgm_data {
	u8 reserved;
	u8 ev_qualifier;
} __attribute__((packed));

#define EV_QUAL_CPU_CHANGE	1
#define EV_QUAL_CAP_CHANGE	3

static struct work_struct sclp_cpu_capability_work;
static struct work_struct sclp_cpu_change_work;

static void sclp_cpu_capability_notify(struct work_struct *work)
{
	int cpu;
	struct device *dev;

	s390_adjust_jiffies();
	pr_warning("cpu capability changed.\n");
	get_online_cpus();
	for_each_online_cpu(cpu) {
		dev = get_cpu_device(cpu);
		kobject_uevent(&dev->kobj, KOBJ_CHANGE);
	}
	put_online_cpus();
}

static void __ref sclp_cpu_change_notify(struct work_struct *work)
{
	smp_rescan_cpus();
}

static void sclp_conf_receiver_fn(struct evbuf_header *evbuf)
{
	struct conf_mgm_data *cdata;

	cdata = (struct conf_mgm_data *)(evbuf + 1);
	switch (cdata->ev_qualifier) {
	case EV_QUAL_CPU_CHANGE:
		schedule_work(&sclp_cpu_change_work);
		break;
	case EV_QUAL_CAP_CHANGE:
		schedule_work(&sclp_cpu_capability_work);
		break;
	}
}

static struct sclp_register sclp_conf_register =
{
	.receive_mask = EVTYP_CONFMGMDATA_MASK,
	.receiver_fn  = sclp_conf_receiver_fn,
};

static int __init sclp_conf_init(void)
{
	INIT_WORK(&sclp_cpu_capability_work, sclp_cpu_capability_notify);
	INIT_WORK(&sclp_cpu_change_work, sclp_cpu_change_notify);
	return sclp_register(&sclp_conf_register);
}

__initcall(sclp_conf_init);
