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
#define pr_fmt(fmt)	"gcov: " fmt

#include <beep/init.h>
#include <beep/module.h>
#include <beep/mutex.h>
#include "gcov.h"

static struct gcov_info *gcov_info_head;
static int gcov_events_enabled;
static DEFINE_MUTEX(gcov_lock);

/*
 * __gcov_init is called by gcc-generated constructor code for each object
 * file compiled with -fprofile-arcs.
 */
void __gcov_init(struct gcov_info *info)
{
	static unsigned int gcov_version;

	mutex_lock(&gcov_lock);
	if (gcov_version == 0) {
		gcov_version = info->version;
		/*
		 * Printing gcc's version magic may prove useful for debugging
		 * incompatibility reports.
		 */
		pr_info("version magic: 0x%x\n", gcov_version);
	}
	/*
	 * Add new profiling data structure to list and inform event
	 * listener.
	 */
	info->next = gcov_info_head;
	gcov_info_head = info;
	if (gcov_events_enabled)
		gcov_event(GCOV_ADD, info);
	mutex_unlock(&gcov_lock);
}
EXPORT_SYMBOL(__gcov_init);

/*
 * These functions may be referenced by gcc-generated profiling code but serve
 * no function for kernel profiling.
 */
void __gcov_flush(void)
{
	/* Unused. */
}
EXPORT_SYMBOL(__gcov_flush);

void __gcov_merge_add(gcov_type *counters, unsigned int n_counters)
{
	/* Unused. */
}
EXPORT_SYMBOL(__gcov_merge_add);

void __gcov_merge_single(gcov_type *counters, unsigned int n_counters)
{
	/* Unused. */
}
EXPORT_SYMBOL(__gcov_merge_single);

void __gcov_merge_delta(gcov_type *counters, unsigned int n_counters)
{
	/* Unused. */
}
EXPORT_SYMBOL(__gcov_merge_delta);

/**
 * gcov_enable_events - enable event reporting through gcov_event()
 *
 * Turn on reporting of profiling data load/unload-events through the
 * gcov_event() callback. Also replay all previous events once. This function
 * is needed because some events are potentially generated too early for the
 * callback implementation to handle them initially.
 */
void gcov_enable_events(void)
{
	struct gcov_info *info;

	mutex_lock(&gcov_lock);
	gcov_events_enabled = 1;
	/* Perform event callback for previously registered entries. */
	for (info = gcov_info_head; info; info = info->next)
		gcov_event(GCOV_ADD, info);
	mutex_unlock(&gcov_lock);
}

#ifdef CONFIG_MODULES
static inline int within(void *addr, void *start, unsigned long size)
{
	return ((addr >= start) && (addr < start + size));
}

/* Update list and generate events when modules are unloaded. */
static int gcov_module_notifier(struct notifier_block *nb, unsigned long event,
				void *data)
{
	struct module *mod = data;
	struct gcov_info *info;
	struct gcov_info *prev;

	if (event != MODULE_STATE_GOING)
		return NOTIFY_OK;
	mutex_lock(&gcov_lock);
	prev = NULL;
	/* Remove entries located in module from linked list. */
	for (info = gcov_info_head; info; info = info->next) {
		if (within(info, mod->module_core, mod->core_size)) {
			if (prev)
				prev->next = info->next;
			else
				gcov_info_head = info->next;
			if (gcov_events_enabled)
				gcov_event(GCOV_REMOVE, info);
		} else
			prev = info;
	}
	mutex_unlock(&gcov_lock);

	return NOTIFY_OK;
}

static struct notifier_block gcov_nb = {
	.notifier_call	= gcov_module_notifier,
};

static int __init gcov_init(void)
{
	return register_module_notifier(&gcov_nb);
}
device_initcall(gcov_init);
#endif /* CONFIG_MODULES */
