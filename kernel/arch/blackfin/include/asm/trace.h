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
#ifndef _BLACKFIN_TRACE_
#define _BLACKFIN_TRACE_

/* Normally, we use ON, but you can't turn on software expansion until
 * interrupts subsystem is ready
 */

#define BFIN_TRACE_INIT ((CONFIG_DEBUG_BFIN_HWTRACE_COMPRESSION << 4) | 0x03)
#ifdef CONFIG_DEBUG_BFIN_HWTRACE_EXPAND
#define BFIN_TRACE_ON   (BFIN_TRACE_INIT | (CONFIG_DEBUG_BFIN_HWTRACE_EXPAND << 2))
#else
#define BFIN_TRACE_ON   (BFIN_TRACE_INIT)
#endif

#ifndef __ASSEMBLY__
extern unsigned long trace_buff_offset;
extern unsigned long software_trace_buff[];
#if defined(CONFIG_DEBUG_VERBOSE)
extern void decode_address(char *buf, unsigned long address);
extern bool get_instruction(unsigned int *val, unsigned short *address);
#else
static inline void decode_address(char *buf, unsigned long address) { }
static inline bool get_instruction(unsigned int *val, unsigned short *address) { return false; }
#endif

/* Trace Macros for C files */

#ifdef CONFIG_DEBUG_BFIN_HWTRACE_ON

#define trace_buffer_init() bfin_write_TBUFCTL(BFIN_TRACE_INIT)

#define trace_buffer_save(x) \
	do { \
		(x) = bfin_read_TBUFCTL(); \
		bfin_write_TBUFCTL((x) & ~TBUFEN); \
	} while (0)

#define trace_buffer_restore(x) \
	do { \
		bfin_write_TBUFCTL((x));        \
	} while (0)
#else /* DEBUG_BFIN_HWTRACE_ON */

#define trace_buffer_save(x)
#define trace_buffer_restore(x)
#endif /* CONFIG_DEBUG_BFIN_HWTRACE_ON */

#else
/* Trace Macros for Assembly files */

#ifdef CONFIG_DEBUG_BFIN_HWTRACE_ON

#define trace_buffer_stop(preg, dreg)	\
	preg.L = LO(TBUFCTL);		\
	preg.H = HI(TBUFCTL);		\
	dreg = 0x1;			\
	[preg] = dreg;

#define trace_buffer_init(preg, dreg) \
	preg.L = LO(TBUFCTL);         \
	preg.H = HI(TBUFCTL);         \
	dreg = BFIN_TRACE_INIT;       \
	[preg] = dreg;

#define trace_buffer_save(preg, dreg) \
	preg.L = LO(TBUFCTL); \
	preg.H = HI(TBUFCTL); \
	dreg = [preg]; \
	[--sp] = dreg; \
	dreg = 0x1; \
	[preg] = dreg;

#define trace_buffer_restore(preg, dreg) \
	preg.L = LO(TBUFCTL); \
	preg.H = HI(TBUFCTL); \
	dreg = [sp++]; \
	[preg] = dreg;

#else /* CONFIG_DEBUG_BFIN_HWTRACE_ON */

#define trace_buffer_stop(preg, dreg)
#define trace_buffer_init(preg, dreg)
#define trace_buffer_save(preg, dreg)
#define trace_buffer_restore(preg, dreg)

#endif /* CONFIG_DEBUG_BFIN_HWTRACE_ON */

#ifdef CONFIG_DEBUG_BFIN_NO_KERN_HWTRACE
# define DEBUG_HWTRACE_SAVE(preg, dreg)    trace_buffer_save(preg, dreg)
# define DEBUG_HWTRACE_RESTORE(preg, dreg) trace_buffer_restore(preg, dreg)
#else
# define DEBUG_HWTRACE_SAVE(preg, dreg)
# define DEBUG_HWTRACE_RESTORE(preg, dreg)
#endif

#endif /* __ASSEMBLY__ */

#endif				/* _BLACKFIN_TRACE_ */
