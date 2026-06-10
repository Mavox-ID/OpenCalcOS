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

/* sparse isn't too happy with all macros... */
#ifndef __CHECKER__
#include <net/cfg80211.h>
#include "driver-ops.h"
#include "debug.h"
#define CREATE_TRACE_POINTS
#include "trace.h"

#ifdef CONFIG_MAC80211_MESSAGE_TRACING
void __sdata_info(const char *fmt, ...)
{
	struct va_format vaf = {
		.fmt = fmt,
	};
	va_list args;

	va_start(args, fmt);
	vaf.va = &args;

	pr_info("%pV", &vaf);
	trace_mac80211_info(&vaf);
	va_end(args);
}

void __sdata_dbg(bool print, const char *fmt, ...)
{
	struct va_format vaf = {
		.fmt = fmt,
	};
	va_list args;

	va_start(args, fmt);
	vaf.va = &args;

	if (print)
		pr_debug("%pV", &vaf);
	trace_mac80211_dbg(&vaf);
	va_end(args);
}

void __sdata_err(const char *fmt, ...)
{
	struct va_format vaf = {
		.fmt = fmt,
	};
	va_list args;

	va_start(args, fmt);
	vaf.va = &args;

	pr_err("%pV", &vaf);
	trace_mac80211_err(&vaf);
	va_end(args);
}

void __wiphy_dbg(struct wiphy *wiphy, bool print, const char *fmt, ...)
{
	struct va_format vaf = {
		.fmt = fmt,
	};
	va_list args;

	va_start(args, fmt);
	vaf.va = &args;

	if (print)
		wiphy_dbg(wiphy, "%pV", &vaf);
	trace_mac80211_dbg(&vaf);
	va_end(args);
}
#endif
#endif
