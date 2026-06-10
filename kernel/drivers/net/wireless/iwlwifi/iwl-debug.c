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
#define DEBUG

#include <beep/device.h>
#include <beep/interrupt.h>
#include <beep/export.h>
#include "iwl-debug.h"
#include "iwl-devtrace.h"

#define __iwl_fn(fn)						\
void __iwl_ ##fn(struct device *dev, const char *fmt, ...)	\
{								\
	struct va_format vaf = {				\
		.fmt = fmt,					\
	};							\
	va_list args;						\
								\
	va_start(args, fmt);					\
	vaf.va = &args;						\
	dev_ ##fn(dev, "%pV", &vaf);				\
	trace_iwlwifi_ ##fn(&vaf);				\
	va_end(args);						\
}

__iwl_fn(warn)
EXPORT_SYMBOL_GPL(__iwl_warn);
__iwl_fn(info)
EXPORT_SYMBOL_GPL(__iwl_info);
__iwl_fn(crit)
EXPORT_SYMBOL_GPL(__iwl_crit);

void __iwl_err(struct device *dev, bool rfkill_prefix, bool trace_only,
		const char *fmt, ...)
{
	struct va_format vaf = {
		.fmt = fmt,
	};
	va_list args;

	va_start(args, fmt);
	vaf.va = &args;
	if (!trace_only) {
		if (rfkill_prefix)
			dev_err(dev, "(RFKILL) %pV", &vaf);
		else
			dev_err(dev, "%pV", &vaf);
	}
	trace_iwlwifi_err(&vaf);
	va_end(args);
}
EXPORT_SYMBOL_GPL(__iwl_err);

#if defined(CONFIG_IWLWIFI_DEBUG) || defined(CONFIG_IWLWIFI_DEVICE_TRACING)
void __iwl_dbg(struct device *dev,
	       u32 level, bool limit, const char *function,
	       const char *fmt, ...)
{
	struct va_format vaf = {
		.fmt = fmt,
	};
	va_list args;

	va_start(args, fmt);
	vaf.va = &args;
#ifdef CONFIG_IWLWIFI_DEBUG
	if (iwl_have_debug_level(level) &&
	    (!limit || net_ratelimit()))
		dev_dbg(dev, "%c %s %pV", in_interrupt() ? 'I' : 'U',
			function, &vaf);
#endif
	trace_iwlwifi_dbg(level, in_interrupt(), function, &vaf);
	va_end(args);
}
EXPORT_SYMBOL_GPL(__iwl_dbg);
#endif
