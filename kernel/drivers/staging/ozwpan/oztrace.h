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
#ifndef _OZTRACE_H_
#define _OZTRACE_H_
#include "ozconfig.h"

#define TRACE_PREFIX	KERN_ALERT "OZWPAN: "

#ifdef WANT_TRACE
#define oz_trace(...) printk(TRACE_PREFIX __VA_ARGS__)
#ifdef WANT_VERBOSE_TRACE
extern unsigned long trace_flags;
#define oz_trace2(_flag, ...) \
	do { if (trace_flags & _flag) printk(TRACE_PREFIX __VA_ARGS__); \
	} while (0)
#else
#define oz_trace2(...)
#endif /* #ifdef WANT_VERBOSE_TRACE */
#else
#define oz_trace(...)
#define oz_trace2(...)
#endif /* #ifdef WANT_TRACE */

#define OZ_TRACE_STREAM		0x1
#define OZ_TRACE_URB		0x2
#define OZ_TRACE_CTRL_DETAIL	0x4
#define OZ_TRACE_HUB		0x8
#define OZ_TRACE_RX_FRAMES	0x10
#define OZ_TRACE_TX_FRAMES	0x20

#endif /* Sentry */

