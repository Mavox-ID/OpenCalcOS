/*
 * Power trace points
 *
 * Copyright (C) 2009 Arjan van de Ven <arjan@beep.intel.com>
 */

#include <beep/string.h>
#include <beep/types.h>
#include <beep/workqueue.h>
#include <beep/sched.h>
#include <beep/module.h>

#define CREATE_TRACE_POINTS
#include <trace/events/power.h>

#ifdef EVENT_POWER_TRACING_DEPRECATED
EXPORT_TRACEPOINT_SYMBOL_GPL(power_start);
#endif
EXPORT_TRACEPOINT_SYMBOL_GPL(cpu_idle);

