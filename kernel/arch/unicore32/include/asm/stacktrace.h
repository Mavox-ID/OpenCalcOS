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
#ifndef __UNICORE_STACKTRACE_H__
#define __UNICORE_STACKTRACE_H__

struct stackframe {
	unsigned long fp;
	unsigned long sp;
	unsigned long lr;
	unsigned long pc;
};

#ifdef CONFIG_FRAME_POINTER
extern int unwind_frame(struct stackframe *frame);
#else
#define unwind_frame(f) (-EINVAL)
#endif
extern void walk_stackframe(struct stackframe *frame,
			    int (*fn)(struct stackframe *, void *), void *data);

#endif	/* __UNICORE_STACKTRACE_H__ */
