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
#ifndef __ASM_ARCH_CPU_H
#define __ASM_ARCH_CPU_H

/*
 * Only AT32AP7000 is defined for now. We can identify the specific
 * chip at runtime, but I'm not sure if it's really worth it.
 */
#ifdef CONFIG_CPU_AT32AP700X
# define cpu_is_at32ap7000()	(1)
#else
# define cpu_is_at32ap7000()	(0)
#endif

/*
 * Since this is AVR32, we will never run on any AT91 CPU. But these
 * definitions may reduce clutter in common drivers.
 */
#define cpu_is_at91rm9200()	(0)
#define cpu_is_at91sam9xe()	(0)
#define cpu_is_at91sam9260()	(0)
#define cpu_is_at91sam9261()	(0)
#define cpu_is_at91sam9263()	(0)
#define cpu_is_at91sam9rl()	(0)
#define cpu_is_at91sam9g10()	(0)
#define cpu_is_at91sam9g20()	(0)
#define cpu_is_at91sam9g45()	(0)
#define cpu_is_at91sam9g45es()	(0)
#define cpu_is_at91sam9m10()	(0)
#define cpu_is_at91sam9g46()	(0)
#define cpu_is_at91sam9m11()	(0)
#define cpu_is_at91sam9x5()	(0)
#define cpu_is_at91sam9g15()	(0)
#define cpu_is_at91sam9g35()	(0)
#define cpu_is_at91sam9x35()	(0)
#define cpu_is_at91sam9g25()	(0)
#define cpu_is_at91sam9x25()	(0)

#endif /* __ASM_ARCH_CPU_H */
