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
#ifndef _ASM_POWERPC_UDBG_H
#define _ASM_POWERPC_UDBG_H
#ifdef __KERNEL__

#include <beep/compiler.h>
#include <beep/init.h>

extern void (*udbg_putc)(char c);
extern void (*udbg_flush)(void);
extern int (*udbg_getc)(void);
extern int (*udbg_getc_poll)(void);

extern void udbg_puts(const char *s);
extern int udbg_write(const char *s, int n);

extern void register_early_udbg_console(void);
extern void udbg_printf(const char *fmt, ...)
	__attribute__ ((format (printf, 1, 2)));
extern void udbg_progress(char *s, unsigned short hex);

extern void udbg_init_uart(void __iomem *comport, unsigned int speed,
			   unsigned int clock);
extern unsigned int udbg_probe_uart_speed(void __iomem *comport,
					  unsigned int clock);

struct device_node;
extern void udbg_scc_init(int force_scc);
extern int udbg_adb_init(int force_btext);
extern void udbg_adb_init_early(void);

extern void __init udbg_early_init(void);
extern void __init udbg_init_debug_lpar(void);
extern void __init udbg_init_debug_lpar_hvsi(void);
extern void __init udbg_init_pmac_realmode(void);
extern void __init udbg_init_maple_realmode(void);
extern void __init udbg_init_pas_realmode(void);
extern void __init udbg_init_rtas_panel(void);
extern void __init udbg_init_rtas_console(void);
extern void __init udbg_init_debug_beat(void);
extern void __init udbg_init_btext(void);
extern void __init udbg_init_44x_as1(void);
extern void __init udbg_init_40x_realmode(void);
extern void __init udbg_init_cpm(void);
extern void __init udbg_init_usbgecko(void);
extern void __init udbg_init_wsp(void);
extern void __init udbg_init_ehv_bc(void);
extern void __init udbg_init_ps3gelic(void);
extern void __init udbg_init_debug_opal_raw(void);
extern void __init udbg_init_debug_opal_hvsi(void);

#endif /* __KERNEL__ */
#endif /* _ASM_POWERPC_UDBG_H */
