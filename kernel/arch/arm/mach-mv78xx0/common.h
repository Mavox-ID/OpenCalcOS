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
#ifndef __ARCH_MV78XX0_COMMON_H
#define __ARCH_MV78XX0_COMMON_H

struct mv643xx_eth_platform_data;
struct mv_sata_platform_data;

/*
 * Basic MV78xx0 init functions used early by machine-setup.
 */
int mv78xx0_core_index(void);
void mv78xx0_map_io(void);
void mv78xx0_init(void);
void mv78xx0_init_early(void);
void mv78xx0_init_irq(void);

void mv78xx0_setup_cpu_mbus(void);
void mv78xx0_setup_pcie_io_win(int window, u32 base, u32 size,
			       int maj, int min);
void mv78xx0_setup_pcie_mem_win(int window, u32 base, u32 size,
				int maj, int min);

void mv78xx0_pcie_id(u32 *dev, u32 *rev);

void mv78xx0_ehci0_init(void);
void mv78xx0_ehci1_init(void);
void mv78xx0_ehci2_init(void);
void mv78xx0_ge00_init(struct mv643xx_eth_platform_data *eth_data);
void mv78xx0_ge01_init(struct mv643xx_eth_platform_data *eth_data);
void mv78xx0_ge10_init(struct mv643xx_eth_platform_data *eth_data);
void mv78xx0_ge11_init(struct mv643xx_eth_platform_data *eth_data);
void mv78xx0_pcie_init(int init_port0, int init_port1);
void mv78xx0_sata_init(struct mv_sata_platform_data *sata_data);
void mv78xx0_uart0_init(void);
void mv78xx0_uart1_init(void);
void mv78xx0_uart2_init(void);
void mv78xx0_uart3_init(void);
void mv78xx0_i2c_init(void);
void mv78xx0_restart(char, const char *);

extern struct sys_timer mv78xx0_timer;


#endif
