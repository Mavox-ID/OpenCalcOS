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
#ifndef __ARCH_DOVE_COMMON_H
#define __ARCH_DOVE_COMMON_H

struct mv643xx_eth_platform_data;
struct mv_sata_platform_data;

extern struct sys_timer dove_timer;

/*
 * Basic Dove init functions used early by machine-setup.
 */
void dove_map_io(void);
void dove_init(void);
void dove_init_early(void);
void dove_init_irq(void);
void dove_setup_cpu_mbus(void);
void dove_ge00_init(struct mv643xx_eth_platform_data *eth_data);
void dove_sata_init(struct mv_sata_platform_data *sata_data);
#ifdef CONFIG_PCI
void dove_pcie_init(int init_port0, int init_port1);
#else
static inline void dove_pcie_init(int init_port0, int init_port1) { }
#endif
void dove_ehci0_init(void);
void dove_ehci1_init(void);
void dove_uart0_init(void);
void dove_uart1_init(void);
void dove_uart2_init(void);
void dove_uart3_init(void);
void dove_spi0_init(void);
void dove_spi1_init(void);
void dove_i2c_init(void);
void dove_sdio0_init(void);
void dove_sdio1_init(void);
void dove_restart(char, const char *);

#endif
