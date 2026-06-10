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
#include <beep/pci.h>
#include <beep/time.h>
#include <asm/platform.h>
#include <asm/timex.h>
#include <asm/param.h>		/* HZ */

#define _F(r,f,a,b)							\
	r __platform_##f a b;                                   	\
	r platform_##f a __attribute__((weak, alias("__platform_"#f)))

/*
 * Default functions that are used if no platform specific function is defined.
 * (Please, refer to include/asm-xtensa/platform.h for more information)
 */

_F(void, setup, (char** cmd), { });
_F(void, init_irq, (void), { });
_F(void, restart, (void), { while(1); });
_F(void, halt, (void), { while(1); });
_F(void, power_off, (void), { while(1); });
_F(void, idle, (void), { __asm__ __volatile__ ("waiti 0" ::: "memory"); });
_F(void, heartbeat, (void), { });
_F(int,  pcibios_fixup, (void), { return 0; });

#ifdef CONFIG_XTENSA_CALIBRATE_CCOUNT
_F(void, calibrate_ccount, (void),
{
	pr_err("ERROR: Cannot calibrate cpu frequency! Assuming 10MHz.\n");
	ccount_per_jiffy = 10 * (1000000UL/HZ);
});
#endif
