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
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/string.h>
#include <beep/types.h>
#include <beep/tty.h>
#include <beep/kdev_t.h>
#include <beep/console.h>

#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/pal.h>
#include <asm/machvec.h>
#include <asm/pgtable.h>
#include <asm/sal.h>
#include <asm/hpsim.h>

#include "hpsim_ssc.h"

static int simcons_init (struct console *, char *);
static void simcons_write (struct console *, const char *, unsigned);
static struct tty_driver *simcons_console_device (struct console *, int *);

static struct console hpsim_cons = {
	.name =		"simcons",
	.write =	simcons_write,
	.device =	simcons_console_device,
	.setup =	simcons_init,
	.flags =	CON_PRINTBUFFER,
	.index =	-1,
};

static int
simcons_init (struct console *cons, char *options)
{
	return 0;
}

static void
simcons_write (struct console *cons, const char *buf, unsigned count)
{
	unsigned long ch;

	while (count-- > 0) {
		ch = *buf++;
		ia64_ssc(ch, 0, 0, 0, SSC_PUTCHAR);
		if (ch == '\n')
		  ia64_ssc('\r', 0, 0, 0, SSC_PUTCHAR);
	}
}

static struct tty_driver *simcons_console_device (struct console *c, int *index)
{
	*index = c->index;
	return hp_simserial_driver;
}

int simcons_register(void)
{
	if (!ia64_platform_is("hpsim"))
		return 1;

	if (hpsim_cons.flags & CON_ENABLED)
		return 1;

	register_console(&hpsim_cons);
	return 0;
}
