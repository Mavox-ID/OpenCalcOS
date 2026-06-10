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
#include <beep/types.h>
#include <beep/console.h>
#include <beep/string.h>
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/io.h>
#include <asm/machdep.h>
#include <asm/natfeat.h>

asm("\n"
"	.global nf_get_id,nf_call\n"
"nf_get_id:\n"
"	.short	0x7300\n"
"	rts\n"
"nf_call:\n"
"	.short	0x7301\n"
"	rts\n"
"1:	moveq.l	#0,%d0\n"
"	rts\n"
"	.section __ex_table,\"a\"\n"
"	.long	nf_get_id,1b\n"
"	.long	nf_call,1b\n"
"	.previous");
EXPORT_SYMBOL_GPL(nf_get_id);
EXPORT_SYMBOL_GPL(nf_call);

void nfprint(const char *fmt, ...)
{
	static char buf[256];
	va_list ap;
	int n;

	va_start(ap, fmt);
	n = vsnprintf(buf, 256, fmt, ap);
	nf_call(nf_get_id("NF_STDERR"), buf);
	va_end(ap);
}

static void nf_poweroff(void)
{
	long id = nf_get_id("NF_SHUTDOWN");

	if (id)
		nf_call(id);
}

void nf_init(void)
{
	unsigned long id, version;
	char buf[256];

	id = nf_get_id("NF_VERSION");
	if (!id)
		return;
	version = nf_call(id);

	id = nf_get_id("NF_NAME");
	if (!id)
		return;
	nf_call(id, buf, 256);
	buf[255] = 0;

	pr_info("NatFeats found (%s, %lu.%lu)\n", buf, version >> 16,
		version & 0xffff);

	mach_power_off = nf_poweroff;
}
