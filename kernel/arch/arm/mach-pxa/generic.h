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
struct irq_data;
struct sys_timer;

extern struct sys_timer pxa_timer;

extern void __init pxa_map_io(void);

extern unsigned int get_clk_frequency_khz(int info);

#define SET_BANK(__nr,__start,__size) \
	mi->bank[__nr].start = (__start), \
	mi->bank[__nr].size = (__size)

#define ARRAY_AND_SIZE(x)	(x), ARRAY_SIZE(x)

#ifdef CONFIG_PXA25x
extern unsigned pxa25x_get_clk_frequency_khz(int);
#else
#define pxa25x_get_clk_frequency_khz(x)		(0)
#endif

#ifdef CONFIG_PXA27x
extern unsigned pxa27x_get_clk_frequency_khz(int);
#else
#define pxa27x_get_clk_frequency_khz(x)		(0)
#endif

#if defined(CONFIG_PXA25x) || defined(CONFIG_PXA27x)
extern void pxa2xx_clear_reset_status(unsigned int);
#else
static inline void pxa2xx_clear_reset_status(unsigned int mask) {}
#endif

#ifdef CONFIG_PXA3xx
extern unsigned pxa3xx_get_clk_frequency_khz(int);
#else
#define pxa3xx_get_clk_frequency_khz(x)		(0)
#endif

extern struct syscore_ops pxa_irq_syscore_ops;
extern struct syscore_ops pxa2xx_mfp_syscore_ops;
extern struct syscore_ops pxa3xx_mfp_syscore_ops;

void __init pxa_set_ffuart_info(void *info);
void __init pxa_set_btuart_info(void *info);
void __init pxa_set_stuart_info(void *info);
void __init pxa_set_hwuart_info(void *info);

void pxa_restart(char, const char *);
