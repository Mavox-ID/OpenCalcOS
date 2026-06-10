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
#ifndef __UNICORE_BUG_H__
#define __UNICORE_BUG_H__

#include <asm-generic/bug.h>

struct pt_regs;
struct siginfo;

extern void die(const char *msg, struct pt_regs *regs, int err);
extern void uc32_notify_die(const char *str, struct pt_regs *regs,
		struct siginfo *info, unsigned long err, unsigned long trap);

#endif /* __UNICORE_BUG_H__ */
