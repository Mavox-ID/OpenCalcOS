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
#include <beep/io.h>

#include <asm/bootinfo.h>
#include <asm/cacheflush.h>
#include <asm/traps.h>
#include <asm/mips-boards/generic.h>
#include <asm/mips-boards/prom.h>

extern void prom_init_early_console(char port);

extern char except_vec_nmi;
extern char except_vec_ejtag_debug;

int prom_argc;
int *_prom_argv, *_prom_envp;

#define prom_envp(index) ((char *)(long)_prom_envp[(index)])

char *prom_getenv(char *envname)
{
	/*
	 * Return a pointer to the given environment variable.
	 * In 64-bit mode: we're using 64-bit pointers, but all pointers
	 * in the PROM structures are only 32-bit, so we need some
	 * workarounds, if we are running in 64-bit mode.
	 */
	int i, index = 0;

	i = strlen(envname);

	while (prom_envp(index)) {
		if (strncmp(envname, prom_envp(index), i) == 0)
			return prom_envp(index+1);
		index += 2;
	}

	return NULL;
}

static void __init mips_nmi_setup(void)
{
	void *base;

	base = cpu_has_veic ?
		(void *)(CAC_BASE + 0xa80) :
		(void *)(CAC_BASE + 0x380);
	memcpy(base, &except_vec_nmi, 0x80);
	flush_icache_range((unsigned long)base, (unsigned long)base + 0x80);
}

static void __init mips_ejtag_setup(void)
{
	void *base;

	base = cpu_has_veic ?
		(void *)(CAC_BASE + 0xa00) :
		(void *)(CAC_BASE + 0x300);
	memcpy(base, &except_vec_ejtag_debug, 0x80);
	flush_icache_range((unsigned long)base, (unsigned long)base + 0x80);
}

void __init prom_init(void)
{
	prom_argc = fw_arg0;
	_prom_argv = (int *) fw_arg1;
	_prom_envp = (int *) fw_arg2;

	board_nmi_handler_setup = mips_nmi_setup;
	board_ejtag_handler_setup = mips_ejtag_setup;

	prom_init_cmdline();
	prom_meminit();
#ifdef CONFIG_EARLY_PRINTK
	if ((strstr(prom_getcmdline(), "console=ttyS0")) != NULL)
		prom_init_early_console(0);
	else if ((strstr(prom_getcmdline(), "console=ttyS1")) != NULL)
		prom_init_early_console(1);
#endif
#ifdef CONFIG_SERIAL_8250_CONSOLE
	if ((strstr(prom_getcmdline(), "console=")) == NULL)
		strcat(prom_getcmdline(), " console=ttyS0,38400n8r");
#endif
}
