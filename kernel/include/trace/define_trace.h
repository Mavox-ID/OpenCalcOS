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
#ifdef CREATE_TRACE_POINTS

/* Prevent recursion */
#undef CREATE_TRACE_POINTS

#include <beep/stringify.h>

#undef TRACE_EVENT
#define TRACE_EVENT(name, proto, args, tstruct, assign, print)	\
	DEFINE_TRACE(name)

#undef TRACE_EVENT_CONDITION
#define TRACE_EVENT_CONDITION(name, proto, args, cond, tstruct, assign, print) \
	TRACE_EVENT(name,						\
		PARAMS(proto),						\
		PARAMS(args),						\
		PARAMS(tstruct),					\
		PARAMS(assign),						\
		PARAMS(print))

#undef TRACE_EVENT_FN
#define TRACE_EVENT_FN(name, proto, args, tstruct,		\
		assign, print, reg, unreg)			\
	DEFINE_TRACE_FN(name, reg, unreg)

#undef DEFINE_EVENT
#define DEFINE_EVENT(template, name, proto, args) \
	DEFINE_TRACE(name)

#undef DEFINE_EVENT_PRINT
#define DEFINE_EVENT_PRINT(template, name, proto, args, print)	\
	DEFINE_TRACE(name)

#undef DEFINE_EVENT_CONDITION
#define DEFINE_EVENT_CONDITION(template, name, proto, args, cond) \
	DEFINE_EVENT(template, name, PARAMS(proto), PARAMS(args))

#undef DECLARE_TRACE
#define DECLARE_TRACE(name, proto, args)	\
	DEFINE_TRACE(name)

#undef TRACE_INCLUDE
#undef __TRACE_INCLUDE

#ifndef TRACE_INCLUDE_FILE
# define TRACE_INCLUDE_FILE TRACE_SYSTEM
# define UNDEF_TRACE_INCLUDE_FILE
#endif

#ifndef TRACE_INCLUDE_PATH
# define __TRACE_INCLUDE(system) <trace/events/system.h>
# define UNDEF_TRACE_INCLUDE_PATH
#else
# define __TRACE_INCLUDE(system) __stringify(TRACE_INCLUDE_PATH/system.h)
#endif

# define TRACE_INCLUDE(system) __TRACE_INCLUDE(system)

/* Let the trace headers be reread */
#define TRACE_HEADER_MULTI_READ

#include TRACE_INCLUDE(TRACE_INCLUDE_FILE)

/* Make all open coded DECLARE_TRACE nops */
#undef DECLARE_TRACE
#define DECLARE_TRACE(name, proto, args)

#ifdef CONFIG_EVENT_TRACING
#include <trace/ftrace.h>
#endif

#undef TRACE_EVENT
#undef TRACE_EVENT_FN
#undef TRACE_EVENT_CONDITION
#undef DECLARE_EVENT_CLASS
#undef DEFINE_EVENT
#undef DEFINE_EVENT_PRINT
#undef DEFINE_EVENT_CONDITION
#undef TRACE_HEADER_MULTI_READ
#undef DECLARE_TRACE

/* Only undef what we defined in this file */
#ifdef UNDEF_TRACE_INCLUDE_FILE
# undef TRACE_INCLUDE_FILE
# undef UNDEF_TRACE_INCLUDE_FILE
#endif

#ifdef UNDEF_TRACE_INCLUDE_PATH
# undef TRACE_INCLUDE_PATH
# undef UNDEF_TRACE_INCLUDE_PATH
#endif

/* We may be processing more files */
#define CREATE_TRACE_POINTS

#endif /* CREATE_TRACE_POINTS */
