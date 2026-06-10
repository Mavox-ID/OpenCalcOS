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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/string.h>
#include <beep/irqflags.h>
#include <asm/setup.h>
#include <hv/hypervisor.h>

static void early_hv_write(struct console *con, const char *s, unsigned n)
{
	hv_console_write((HV_VirtAddr) s, n);
}

static struct console early_hv_console = {
	.name =		"earlyhv",
	.write =	early_hv_write,
	.flags =	CON_PRINTBUFFER,
	.index =	-1,
};

/* Direct interface for emergencies */
static struct console *early_console = &early_hv_console;
static int early_console_initialized;
static int early_console_complete;

static void early_vprintk(const char *fmt, va_list ap)
{
	char buf[512];
	int n = vscnprintf(buf, sizeof(buf), fmt, ap);
	early_console->write(early_console, buf, n);
}

void early_printk(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	early_vprintk(fmt, ap);
	va_end(ap);
}

void early_panic(const char *fmt, ...)
{
	va_list ap;
	arch_local_irq_disable_all();
	va_start(ap, fmt);
	early_printk("Kernel panic - not syncing: ");
	early_vprintk(fmt, ap);
	early_console->write(early_console, "\n", 1);
	va_end(ap);
	dump_stack();
	hv_halt();
}

static int __initdata keep_early;

static int __init setup_early_printk(char *str)
{
	if (early_console_initialized)
		return 1;

	if (str != NULL && strncmp(str, "keep", 4) == 0)
		keep_early = 1;

	early_console = &early_hv_console;
	early_console_initialized = 1;
	register_console(early_console);

	return 0;
}

void __init disable_early_printk(void)
{
	early_console_complete = 1;
	if (!early_console_initialized || !early_console)
		return;
	if (!keep_early) {
		early_printk("disabling early console\n");
		unregister_console(early_console);
		early_console_initialized = 0;
	} else {
		early_printk("keeping early console\n");
	}
}

void warn_early_printk(void)
{
	if (early_console_complete || early_console_initialized)
		return;
	early_printk("\
Machine shutting down before console output is fully initialized.\n\
You may wish to reboot and add the option 'earlyprintk' to your\n\
boot command line to see any diagnostic early console output.\n\
");
}

early_param("earlyprintk", setup_early_printk);
