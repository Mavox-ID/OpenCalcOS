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
struct at91_init_soc {
	int builtin;
	unsigned int *default_irq_priority;
	void (*map_io)(void);
	void (*ioremap_registers)(void);
	void (*register_clocks)(void);
	void (*init)(void);
};

extern struct at91_init_soc at91_boot_soc;
extern struct at91_init_soc at91rm9200_soc;
extern struct at91_init_soc at91sam9260_soc;
extern struct at91_init_soc at91sam9261_soc;
extern struct at91_init_soc at91sam9263_soc;
extern struct at91_init_soc at91sam9g45_soc;
extern struct at91_init_soc at91sam9rl_soc;
extern struct at91_init_soc at91sam9x5_soc;
extern struct at91_init_soc at91sam9n12_soc;

#define AT91_SOC_START(_name)				\
struct at91_init_soc __initdata at91##_name##_soc	\
 __used							\
						= {	\
	.builtin	= 1,				\

#define AT91_SOC_END					\
};

static inline int at91_soc_is_enabled(void)
{
	return at91_boot_soc.builtin;
}

#if !defined(CONFIG_SOC_AT91RM9200)
#define at91rm9200_soc	at91_boot_soc
#endif

#if !defined(CONFIG_SOC_AT91SAM9260)
#define at91sam9260_soc	at91_boot_soc
#endif

#if !defined(CONFIG_SOC_AT91SAM9261)
#define at91sam9261_soc	at91_boot_soc
#endif

#if !defined(CONFIG_SOC_AT91SAM9263)
#define at91sam9263_soc	at91_boot_soc
#endif

#if !defined(CONFIG_SOC_AT91SAM9G45)
#define at91sam9g45_soc	at91_boot_soc
#endif

#if !defined(CONFIG_SOC_AT91SAM9RL)
#define at91sam9rl_soc	at91_boot_soc
#endif

#if !defined(CONFIG_SOC_AT91SAM9X5)
#define at91sam9x5_soc	at91_boot_soc
#endif

#if !defined(CONFIG_SOC_AT91SAM9N12)
#define at91sam9n12_soc	at91_boot_soc
#endif
