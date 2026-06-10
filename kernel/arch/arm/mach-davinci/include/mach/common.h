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
#ifndef __ARCH_ARM_MACH_DAVINCI_COMMON_H
#define __ARCH_ARM_MACH_DAVINCI_COMMON_H

#include <beep/compiler.h>
#include <beep/types.h>

struct sys_timer;

extern struct sys_timer davinci_timer;

extern void davinci_irq_init(void);
extern void __iomem *davinci_intc_base;
extern int davinci_intc_type;

struct davinci_timer_instance {
	u32		base;
	u32		bottom_irq;
	u32		top_irq;
	unsigned long	cmp_off;
	unsigned int	cmp_irq;
};

struct davinci_timer_info {
	struct davinci_timer_instance	*timers;
	unsigned int			clockevent_id;
	unsigned int			clocksource_id;
};

struct davinci_gpio_controller;

/*
 * SoC info passed into common davinci modules.
 *
 * Base addresses in this structure should be physical and not virtual.
 * Modules that take such base addresses, should internally ioremap() them to
 * use.
 */
struct davinci_soc_info {
	struct map_desc			*io_desc;
	unsigned long			io_desc_num;
	u32				cpu_id;
	u32				jtag_id;
	u32				jtag_id_reg;
	struct davinci_id		*ids;
	unsigned long			ids_num;
	struct clk_lookup		*cpu_clks;
	u32				*psc_bases;
	unsigned long			psc_bases_num;
	u32				pinmux_base;
	const struct mux_config		*pinmux_pins;
	unsigned long			pinmux_pins_num;
	u32				intc_base;
	int				intc_type;
	u8				*intc_irq_prios;
	unsigned long			intc_irq_num;
	u32				*intc_host_map;
	struct davinci_timer_info	*timer_info;
	int				gpio_type;
	u32				gpio_base;
	unsigned			gpio_num;
	unsigned			gpio_irq;
	unsigned			gpio_unbanked;
	struct davinci_gpio_controller	*gpio_ctlrs;
	int				gpio_ctlrs_num;
	struct platform_device		*serial_dev;
	struct emac_platform_data	*emac_pdata;
	dma_addr_t			sram_dma;
	unsigned			sram_len;
};

extern struct davinci_soc_info davinci_soc_info;

extern void davinci_common_init(struct davinci_soc_info *soc_info);
extern void davinci_init_ide(void);
void davinci_restart(char mode, const char *cmd);
void davinci_init_late(void);

#ifdef CONFIG_DAVINCI_RESET_CLOCKS
int davinci_clk_disable_unused(void);
#else
static inline int davinci_clk_disable_unused(void) { return 0; }
#endif

#ifdef CONFIG_CPU_FREQ
int davinci_cpufreq_init(void);
#else
static inline int davinci_cpufreq_init(void) { return 0; }
#endif

#ifdef CONFIG_SUSPEND
int davinci_pm_init(void);
#else
static inline int davinci_pm_init(void) { return 0; }
#endif

#define SRAM_SIZE	SZ_128K

#endif /* __ARCH_ARM_MACH_DAVINCI_COMMON_H */
