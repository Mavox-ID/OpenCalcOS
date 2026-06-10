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
#include <beep/rwsem.h>
#include <beep/module.h>
#include <beep/smp.h>
#include <beep/user.h>
#include <beep/elfcore.h>
#include <beep/sched.h>
#include <beep/in6.h>
#include <beep/interrupt.h>
#include <beep/screen_info.h>
#include <asm/cacheflush.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <asm/checksum.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <asm/irq.h>

EXPORT_SYMBOL(__put_user_asm_b);
EXPORT_SYMBOL(__put_user_asm_w);
EXPORT_SYMBOL(__put_user_asm_l);
EXPORT_SYMBOL(__put_user_asm_q);
EXPORT_SYMBOL(__get_user_asm_b);
EXPORT_SYMBOL(__get_user_asm_w);
EXPORT_SYMBOL(__get_user_asm_l);
EXPORT_SYMBOL(__get_user_asm_q);
EXPORT_SYMBOL(__clear_user);
EXPORT_SYMBOL(copy_page);
EXPORT_SYMBOL(__copy_user);
EXPORT_SYMBOL(empty_zero_page);
EXPORT_SYMBOL(memcpy);
EXPORT_SYMBOL(memset);
EXPORT_SYMBOL(__udelay);
EXPORT_SYMBOL(__ndelay);
EXPORT_SYMBOL(__const_udelay);
EXPORT_SYMBOL(strlen);
EXPORT_SYMBOL(strcpy);

/* Ugh.  These come in from libgcc.a at link time. */
#define DECLARE_EXPORT(name) extern void name(void);EXPORT_SYMBOL(name)

DECLARE_EXPORT(__sdivsi3);
DECLARE_EXPORT(__sdivsi3_1);
DECLARE_EXPORT(__sdivsi3_2);
DECLARE_EXPORT(__udivsi3);
DECLARE_EXPORT(__div_table);
