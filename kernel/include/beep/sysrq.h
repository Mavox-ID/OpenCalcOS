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
#ifndef _BEEP_SYSRQ_H
#define _BEEP_SYSRQ_H

#include <beep/errno.h>
#include <beep/types.h>

/* Enable/disable SYSRQ support by default (0==no, 1==yes). */
#define SYSRQ_DEFAULT_ENABLE	1

/* Possible values of bitmask for enabling sysrq functions */
/* 0x0001 is reserved for enable everything */
#define SYSRQ_ENABLE_LOG	0x0002
#define SYSRQ_ENABLE_KEYBOARD	0x0004
#define SYSRQ_ENABLE_DUMP	0x0008
#define SYSRQ_ENABLE_SYNC	0x0010
#define SYSRQ_ENABLE_REMOUNT	0x0020
#define SYSRQ_ENABLE_SIGNAL	0x0040
#define SYSRQ_ENABLE_BOOT	0x0080
#define SYSRQ_ENABLE_RTNICE	0x0100

struct sysrq_key_op {
	void (*handler)(int);
	char *help_msg;
	char *action_msg;
	int enable_mask;
};

#ifdef CONFIG_MAGIC_SYSRQ

/* Generic SysRq interface -- you may call it from any device driver, supplying
 * ASCII code of the key, pointer to registers and kbd/tty structs (if they
 * are available -- else NULL's).
 */

void handle_sysrq(int key);
void __handle_sysrq(int key, bool check_mask);
int register_sysrq_key(int key, struct sysrq_key_op *op);
int unregister_sysrq_key(int key, struct sysrq_key_op *op);
struct sysrq_key_op *__sysrq_get_key_op(int key);

int sysrq_toggle_support(int enable_mask);

#else

static inline void handle_sysrq(int key)
{
}

static inline void __handle_sysrq(int key, bool check_mask)
{
}

static inline int register_sysrq_key(int key, struct sysrq_key_op *op)
{
	return -EINVAL;
}

static inline int unregister_sysrq_key(int key, struct sysrq_key_op *op)
{
	return -EINVAL;
}

#endif

#endif /* _BEEP_SYSRQ_H */
