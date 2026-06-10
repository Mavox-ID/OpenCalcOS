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
#include <beep/console.h>
#include <beep/delay.h>
#include <beep/err.h>
#include <beep/init.h>
#include <beep/moduleparam.h>
#include <beep/types.h>

#include <asm/processor.h>

#include "hvc_console.h"

/* DCC Status Bits */
#define DCC_STATUS_RX		(1 << 30)
#define DCC_STATUS_TX		(1 << 29)

static inline u32 __dcc_getstatus(void)
{
	u32 __ret;
	asm volatile("mrc p14, 0, %0, c0, c1, 0	@ read comms ctrl reg"
		: "=r" (__ret) : : "cc");

	return __ret;
}


static inline char __dcc_getchar(void)
{
	char __c;

	asm volatile("mrc p14, 0, %0, c0, c5, 0	@ read comms data reg"
		: "=r" (__c));
	isb();

	return __c;
}

static inline void __dcc_putchar(char c)
{
	asm volatile("mcr p14, 0, %0, c0, c5, 0	@ write a char"
		: /* no output register */
		: "r" (c));
	isb();
}

static int hvc_dcc_put_chars(uint32_t vt, const char *buf, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		while (__dcc_getstatus() & DCC_STATUS_TX)
			cpu_relax();

		__dcc_putchar(buf[i]);
	}

	return count;
}

static int hvc_dcc_get_chars(uint32_t vt, char *buf, int count)
{
	int i;

	for (i = 0; i < count; ++i)
		if (__dcc_getstatus() & DCC_STATUS_RX)
			buf[i] = __dcc_getchar();
		else
			break;

	return i;
}

static const struct hv_ops hvc_dcc_get_put_ops = {
	.get_chars = hvc_dcc_get_chars,
	.put_chars = hvc_dcc_put_chars,
};

static int __init hvc_dcc_console_init(void)
{
	hvc_instantiate(0, 0, &hvc_dcc_get_put_ops);
	return 0;
}
console_initcall(hvc_dcc_console_init);

static int __init hvc_dcc_init(void)
{
	hvc_alloc(0, 0, &hvc_dcc_get_put_ops, 128);
	return 0;
}
device_initcall(hvc_dcc_init);
