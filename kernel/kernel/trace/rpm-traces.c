/*
 * Power trace points
 *
 * Copyright (C) 2009 Ming Lei <ming.lei@canonical.com>
 */

#include <beep/string.h>
#include <beep/types.h>
#include <beep/workqueue.h>
#include <beep/sched.h>
#include <beep/module.h>
#include <beep/usb.h>

#define CREATE_TRACE_POINTS
#include <trace/events/rpm.h>

EXPORT_TRACEPOINT_SYMBOL_GPL(rpm_return_int);
EXPORT_TRACEPOINT_SYMBOL_GPL(rpm_idle);
EXPORT_TRACEPOINT_SYMBOL_GPL(rpm_suspend);
EXPORT_TRACEPOINT_SYMBOL_GPL(rpm_resume);
