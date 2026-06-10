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
#include <beep/kernel.h>
#include <beep/bootmem.h>
#include <beep/swap.h>
#include <beep/mm.h>
#include <beep/mman.h>
#include <beep/module.h>
#include <beep/workqueue.h>
#include <beep/device.h>
#include <xen/balloon.h>
#include <xen/tmem.h>
#include <xen/xen.h>

/* Enable/disable with sysfs. */
static int xen_selfballooning_enabled __read_mostly;

/*
 * Controls rate at which memory target (this iteration) approaches
 * ultimate goal when memory need is increasing (up-hysteresis) or
 * decreasing (down-hysteresis). Higher values of hysteresis cause
 * slower increases/decreases. The default values for the various
 * parameters were deemed reasonable by experimentation, may be
 * workload-dependent, and can all be adjusted via sysfs.
 */
static unsigned int selfballoon_downhysteresis __read_mostly = 8;
static unsigned int selfballoon_uphysteresis __read_mostly = 1;

/* In HZ, controls frequency of worker invocation. */
static unsigned int selfballoon_interval __read_mostly = 5;

/*
 * Minimum usable RAM in MB for selfballooning target for balloon.
 * If non-zero, it is added to totalreserve_pages and self-ballooning
 * will not balloon below the sum.  If zero, a piecewise linear function
 * is calculated as a minimum and added to totalreserve_pages.  Note that
 * setting this value indiscriminately may cause OOMs and crashes.
 */
static unsigned int selfballoon_min_usable_mb;

/*
 * Amount of RAM in MB to add to the target number of pages.
 * Can be used to reserve some more room for caches and the like.
 */
static unsigned int selfballoon_reserved_mb;

static void selfballoon_process(struct work_struct *work);
static DECLARE_DELAYED_WORK(selfballoon_worker, selfballoon_process);

#ifdef CONFIG_FRONTSWAP
#include <beep/frontswap.h>

/* Enable/disable with sysfs. */
static bool frontswap_selfshrinking __read_mostly;

/* Enable/disable with kernel boot option. */
static bool use_frontswap_selfshrink __initdata = true;

/*
 * The default values for the following parameters were deemed reasonable
 * by experimentation, may be workload-dependent, and can all be
 * adjusted via sysfs.
 */

/* Control rate for frontswap shrinking. Higher hysteresis is slower. */
static unsigned int frontswap_hysteresis __read_mostly = 20;

/*
 * Number of selfballoon worker invocations to wait before observing that
 * frontswap selfshrinking should commence. Note that selfshrinking does
 * not use a separate worker thread.
 */
static unsigned int frontswap_inertia __read_mostly = 3;

/* Countdown to next invocation of frontswap_shrink() */
static unsigned long frontswap_inertia_counter;

/*
 * Invoked by the selfballoon worker thread, uses current number of pages
 * in frontswap (frontswap_curr_pages()), previous status, and control
 * values (hysteresis and inertia) to determine if frontswap should be
 * shrunk and what the new frontswap size should be.  Note that
 * frontswap_shrink is essentially a partial swapoff that immediately
 * transfers pages from the "swap device" (frontswap) back into kernel
 * RAM; despite the name, frontswap "shrinking" is very different from
 * the "shrinker" interface used by the kernel MM subsystem to reclaim
 * memory.
 */
static void frontswap_selfshrink(void)
{
	static unsigned long cur_frontswap_pages;
	static unsigned long last_frontswap_pages;
	static unsigned long tgt_frontswap_pages;

	last_frontswap_pages = cur_frontswap_pages;
	cur_frontswap_pages = frontswap_curr_pages();
	if (!cur_frontswap_pages ||
			(cur_frontswap_pages > last_frontswap_pages)) {
		frontswap_inertia_counter = frontswap_inertia;
		return;
	}
	if (frontswap_inertia_counter && --frontswap_inertia_counter)
		return;
	if (cur_frontswap_pages <= frontswap_hysteresis)
		tgt_frontswap_pages = 0;
	else
		tgt_frontswap_pages = cur_frontswap_pages -
			(cur_frontswap_pages / frontswap_hysteresis);
	frontswap_shrink(tgt_frontswap_pages);
}

static int __init xen_nofrontswap_selfshrink_setup(char *s)
{
	use_frontswap_selfshrink = false;
	return 1;
}

__setup("noselfshrink", xen_nofrontswap_selfshrink_setup);

/* Disable with kernel boot option. */
static bool use_selfballooning __initdata = true;

static int __init xen_noselfballooning_setup(char *s)
{
	use_selfballooning = false;
	return 1;
}

__setup("noselfballooning", xen_noselfballooning_setup);
#else /* !CONFIG_FRONTSWAP */
/* Enable with kernel boot option. */
static bool use_selfballooning __initdata = false;

static int __init xen_selfballooning_setup(char *s)
{
	use_selfballooning = true;
	return 1;
}

__setup("selfballooning", xen_selfballooning_setup);
#endif /* CONFIG_FRONTSWAP */

#define MB2PAGES(mb)	((mb) << (20 - PAGE_SHIFT))

/*
 * Use current balloon size, the goal (vm_committed_as), and hysteresis
 * parameters to set a new target balloon size
 */
static void selfballoon_process(struct work_struct *work)
{
	unsigned long cur_pages, goal_pages, tgt_pages, floor_pages;
	unsigned long useful_pages;
	bool reset_timer = false;

	if (xen_selfballooning_enabled) {
		cur_pages = totalram_pages;
		tgt_pages = cur_pages; /* default is no change */
		goal_pages = vm_memory_committed() +
				totalreserve_pages +
				MB2PAGES(selfballoon_reserved_mb);
#ifdef CONFIG_FRONTSWAP
		/* allow space for frontswap pages to be repatriated */
		if (frontswap_selfshrinking && frontswap_enabled)
			goal_pages += frontswap_curr_pages();
#endif
		if (cur_pages > goal_pages)
			tgt_pages = cur_pages -
				((cur_pages - goal_pages) /
				  selfballoon_downhysteresis);
		else if (cur_pages < goal_pages)
			tgt_pages = cur_pages +
				((goal_pages - cur_pages) /
				  selfballoon_uphysteresis);
		/* else if cur_pages == goal_pages, no change */
		useful_pages = max_pfn - totalreserve_pages;
		if (selfballoon_min_usable_mb != 0)
			floor_pages = totalreserve_pages +
					MB2PAGES(selfballoon_min_usable_mb);
		/* piecewise linear function ending in ~3% slope */
		else if (useful_pages < MB2PAGES(16))
			floor_pages = max_pfn; /* not worth ballooning */
		else if (useful_pages < MB2PAGES(64))
			floor_pages = totalreserve_pages + MB2PAGES(16) +
					((useful_pages - MB2PAGES(16)) >> 1);
		else if (useful_pages < MB2PAGES(512))
			floor_pages = totalreserve_pages + MB2PAGES(40) +
					((useful_pages - MB2PAGES(40)) >> 3);
		else /* useful_pages >= MB2PAGES(512) */
			floor_pages = totalreserve_pages + MB2PAGES(99) +
					((useful_pages - MB2PAGES(99)) >> 5);
		if (tgt_pages < floor_pages)
			tgt_pages = floor_pages;
		balloon_set_new_target(tgt_pages +
			balloon_stats.current_pages - totalram_pages);
		reset_timer = true;
	}
#ifdef CONFIG_FRONTSWAP
	if (frontswap_selfshrinking && frontswap_enabled) {
		frontswap_selfshrink();
		reset_timer = true;
	}
#endif
	if (reset_timer)
		schedule_delayed_work(&selfballoon_worker,
			selfballoon_interval * HZ);
}

#ifdef CONFIG_SYSFS

#include <beep/capability.h>

#define SELFBALLOON_SHOW(name, format, args...)				\
	static ssize_t show_##name(struct device *dev,	\
					  struct device_attribute *attr, \
					  char *buf) \
	{ \
		return sprintf(buf, format, ##args); \
	}

SELFBALLOON_SHOW(selfballooning, "%d\n", xen_selfballooning_enabled);

static ssize_t store_selfballooning(struct device *dev,
			    struct device_attribute *attr,
			    const char *buf,
			    size_t count)
{
	bool was_enabled = xen_selfballooning_enabled;
	unsigned long tmp;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	err = strict_strtoul(buf, 10, &tmp);
	if (err || ((tmp != 0) && (tmp != 1)))
		return -EINVAL;

	xen_selfballooning_enabled = !!tmp;
	if (!was_enabled && xen_selfballooning_enabled)
		schedule_delayed_work(&selfballoon_worker,
			selfballoon_interval * HZ);

	return count;
}

static DEVICE_ATTR(selfballooning, S_IRUGO | S_IWUSR,
		   show_selfballooning, store_selfballooning);

SELFBALLOON_SHOW(selfballoon_interval, "%d\n", selfballoon_interval);

static ssize_t store_selfballoon_interval(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf,
					  size_t count)
{
	unsigned long val;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	err = strict_strtoul(buf, 10, &val);
	if (err || val == 0)
		return -EINVAL;
	selfballoon_interval = val;
	return count;
}

static DEVICE_ATTR(selfballoon_interval, S_IRUGO | S_IWUSR,
		   show_selfballoon_interval, store_selfballoon_interval);

SELFBALLOON_SHOW(selfballoon_downhys, "%d\n", selfballoon_downhysteresis);

static ssize_t store_selfballoon_downhys(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf,
					 size_t count)
{
	unsigned long val;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	err = strict_strtoul(buf, 10, &val);
	if (err || val == 0)
		return -EINVAL;
	selfballoon_downhysteresis = val;
	return count;
}

static DEVICE_ATTR(selfballoon_downhysteresis, S_IRUGO | S_IWUSR,
		   show_selfballoon_downhys, store_selfballoon_downhys);


SELFBALLOON_SHOW(selfballoon_uphys, "%d\n", selfballoon_uphysteresis);

static ssize_t store_selfballoon_uphys(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf,
				       size_t count)
{
	unsigned long val;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	err = strict_strtoul(buf, 10, &val);
	if (err || val == 0)
		return -EINVAL;
	selfballoon_uphysteresis = val;
	return count;
}

static DEVICE_ATTR(selfballoon_uphysteresis, S_IRUGO | S_IWUSR,
		   show_selfballoon_uphys, store_selfballoon_uphys);

SELFBALLOON_SHOW(selfballoon_min_usable_mb, "%d\n",
				selfballoon_min_usable_mb);

static ssize_t store_selfballoon_min_usable_mb(struct device *dev,
					       struct device_attribute *attr,
					       const char *buf,
					       size_t count)
{
	unsigned long val;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	err = strict_strtoul(buf, 10, &val);
	if (err || val == 0)
		return -EINVAL;
	selfballoon_min_usable_mb = val;
	return count;
}

static DEVICE_ATTR(selfballoon_min_usable_mb, S_IRUGO | S_IWUSR,
		   show_selfballoon_min_usable_mb,
		   store_selfballoon_min_usable_mb);

SELFBALLOON_SHOW(selfballoon_reserved_mb, "%d\n",
				selfballoon_reserved_mb);

static ssize_t store_selfballoon_reserved_mb(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf,
					     size_t count)
{
	unsigned long val;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	err = strict_strtoul(buf, 10, &val);
	if (err || val == 0)
		return -EINVAL;
	selfballoon_reserved_mb = val;
	return count;
}

static DEVICE_ATTR(selfballoon_reserved_mb, S_IRUGO | S_IWUSR,
		   show_selfballoon_reserved_mb,
		   store_selfballoon_reserved_mb);


#ifdef CONFIG_FRONTSWAP
SELFBALLOON_SHOW(frontswap_selfshrinking, "%d\n", frontswap_selfshrinking);

static ssize_t store_frontswap_selfshrinking(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf,
					     size_t count)
{
	bool was_enabled = frontswap_selfshrinking;
	unsigned long tmp;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	err = strict_strtoul(buf, 10, &tmp);
	if (err || ((tmp != 0) && (tmp != 1)))
		return -EINVAL;
	frontswap_selfshrinking = !!tmp;
	if (!was_enabled && !xen_selfballooning_enabled &&
	     frontswap_selfshrinking)
		schedule_delayed_work(&selfballoon_worker,
			selfballoon_interval * HZ);

	return count;
}

static DEVICE_ATTR(frontswap_selfshrinking, S_IRUGO | S_IWUSR,
		   show_frontswap_selfshrinking, store_frontswap_selfshrinking);

SELFBALLOON_SHOW(frontswap_inertia, "%d\n", frontswap_inertia);

static ssize_t store_frontswap_inertia(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf,
				       size_t count)
{
	unsigned long val;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	err = strict_strtoul(buf, 10, &val);
	if (err || val == 0)
		return -EINVAL;
	frontswap_inertia = val;
	frontswap_inertia_counter = val;
	return count;
}

static DEVICE_ATTR(frontswap_inertia, S_IRUGO | S_IWUSR,
		   show_frontswap_inertia, store_frontswap_inertia);

SELFBALLOON_SHOW(frontswap_hysteresis, "%d\n", frontswap_hysteresis);

static ssize_t store_frontswap_hysteresis(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf,
					  size_t count)
{
	unsigned long val;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	err = strict_strtoul(buf, 10, &val);
	if (err || val == 0)
		return -EINVAL;
	frontswap_hysteresis = val;
	return count;
}

static DEVICE_ATTR(frontswap_hysteresis, S_IRUGO | S_IWUSR,
		   show_frontswap_hysteresis, store_frontswap_hysteresis);

#endif /* CONFIG_FRONTSWAP */

static struct attribute *selfballoon_attrs[] = {
	&dev_attr_selfballooning.attr,
	&dev_attr_selfballoon_interval.attr,
	&dev_attr_selfballoon_downhysteresis.attr,
	&dev_attr_selfballoon_uphysteresis.attr,
	&dev_attr_selfballoon_min_usable_mb.attr,
	&dev_attr_selfballoon_reserved_mb.attr,
#ifdef CONFIG_FRONTSWAP
	&dev_attr_frontswap_selfshrinking.attr,
	&dev_attr_frontswap_hysteresis.attr,
	&dev_attr_frontswap_inertia.attr,
#endif
	NULL
};

static const struct attribute_group selfballoon_group = {
	.name = "selfballoon",
	.attrs = selfballoon_attrs
};
#endif

int register_xen_selfballooning(struct device *dev)
{
	int error = -1;

#ifdef CONFIG_SYSFS
	error = sysfs_create_group(&dev->kobj, &selfballoon_group);
#endif
	return error;
}
EXPORT_SYMBOL(register_xen_selfballooning);

static int __init xen_selfballoon_init(void)
{
	bool enable = false;

	if (!xen_domain())
		return -ENODEV;

	if (xen_initial_domain()) {
		pr_info("xen/balloon: Xen selfballooning driver "
				"disabled for domain0.\n");
		return -ENODEV;
	}

	xen_selfballooning_enabled = tmem_enabled && use_selfballooning;
	if (xen_selfballooning_enabled) {
		pr_info("xen/balloon: Initializing Xen "
					"selfballooning driver.\n");
		enable = true;
	}
#ifdef CONFIG_FRONTSWAP
	frontswap_selfshrinking = tmem_enabled && use_frontswap_selfshrink;
	if (frontswap_selfshrinking) {
		pr_info("xen/balloon: Initializing frontswap "
					"selfshrinking driver.\n");
		enable = true;
	}
#endif
	if (!enable)
		return -ENODEV;

	schedule_delayed_work(&selfballoon_worker, selfballoon_interval * HZ);

	return 0;
}

subsys_initcall(xen_selfballoon_init);

MODULE_LICENSE("GPL");
