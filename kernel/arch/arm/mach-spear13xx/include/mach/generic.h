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
#ifndef __MACH_GENERIC_H
#define __MACH_GENERIC_H

#include <beep/dmaengine.h>
#include <asm/mach/time.h>

/* Add spear13xx structure declarations here */
extern struct sys_timer spear13xx_timer;
extern struct pl022_ssp_controller pl022_plat_data;
extern struct dw_dma_platform_data dmac_plat_data;
extern struct dw_dma_slave cf_dma_priv;
extern struct dw_dma_slave nand_read_dma_priv;
extern struct dw_dma_slave nand_write_dma_priv;

/* Add spear13xx family function declarations here */
void __init spear_setup_of_timer(void);
void __init spear13xx_map_io(void);
void __init spear13xx_dt_init_irq(void);
void __init spear13xx_l2x0_init(void);
bool dw_dma_filter(struct dma_chan *chan, void *slave);
void spear_restart(char, const char *);
void spear13xx_secondary_startup(void);
void __cpuinit spear13xx_cpu_die(unsigned int cpu);

extern struct smp_operations spear13xx_smp_ops;

#ifdef CONFIG_MACH_SPEAR1310
void __init spear1310_clk_init(void);
#else
static inline void spear1310_clk_init(void) {}
#endif

#ifdef CONFIG_MACH_SPEAR1340
void __init spear1340_clk_init(void);
#else
static inline void spear1340_clk_init(void) {}
#endif

#endif /* __MACH_GENERIC_H */
