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
#ifndef __PERF_DEBUG_H
#define __PERF_DEBUG_H

#include <stdbool.h>
#include "event.h"
#include "../ui/helpline.h"

extern int verbose;
extern bool quiet, dump_trace;

int dump_printf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void trace_event(union perf_event *event);

struct ui_progress;
struct perf_error_ops;

#if defined(NEWT_SUPPORT) || defined(GTK2_SUPPORT)

#include "../ui/progress.h"
int ui__error(const char *format, ...) __attribute__((format(printf, 1, 2)));
#include "../ui/util.h"

#else

static inline void ui_progress__update(u64 curr __maybe_unused,
				       u64 total __maybe_unused,
				       const char *title __maybe_unused) {}
static inline void ui_progress__finish(void) {}

#define ui__error(format, arg...) ui__warning(format, ##arg)

static inline int
perf_error__register(struct perf_error_ops *eops __maybe_unused)
{
	return 0;
}

static inline int
perf_error__unregister(struct perf_error_ops *eops __maybe_unused)
{
	return 0;
}

#endif /* NEWT_SUPPORT || GTK2_SUPPORT */

int ui__warning(const char *format, ...) __attribute__((format(printf, 1, 2)));
int ui__error_paranoid(void);

#endif	/* __PERF_DEBUG_H */
