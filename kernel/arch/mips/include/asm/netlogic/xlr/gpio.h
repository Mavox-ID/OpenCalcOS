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
#ifndef _ASM_NLM_GPIO_H
#define _ASM_NLM_GPIO_H

#define GPIO_INT_EN_REG			0
#define GPIO_INPUT_INVERSION_REG	1
#define GPIO_IO_DIR_REG			2
#define GPIO_IO_DATA_WR_REG		3
#define GPIO_IO_DATA_RD_REG		4

#define GPIO_SWRESET_REG		8
#define GPIO_DRAM1_CNTRL_REG		9
#define GPIO_DRAM1_RATIO_REG		10
#define GPIO_DRAM1_RESET_REG		11
#define GPIO_DRAM1_STATUS_REG		12
#define GPIO_DRAM2_CNTRL_REG		13
#define GPIO_DRAM2_RATIO_REG		14
#define GPIO_DRAM2_RESET_REG		15
#define GPIO_DRAM2_STATUS_REG		16

#define GPIO_PWRON_RESET_CFG_REG	21
#define GPIO_BIST_ALL_GO_STATUS_REG	24
#define GPIO_BIST_CPU_GO_STATUS_REG	25
#define GPIO_BIST_DEV_GO_STATUS_REG	26

#define GPIO_FUSE_BANK_REG		35
#define GPIO_CPU_RESET_REG		40
#define GPIO_RNG_REG			43

#define PWRON_RESET_PCMCIA_BOOT		17

#define GPIO_LED_BITMAP			0x1700000
#define GPIO_LED_0_SHIFT		20
#define GPIO_LED_1_SHIFT		24

#define GPIO_LED_OUTPUT_CODE_RESET	0x01
#define GPIO_LED_OUTPUT_CODE_HARD_RESET 0x02
#define GPIO_LED_OUTPUT_CODE_SOFT_RESET 0x03
#define GPIO_LED_OUTPUT_CODE_MAIN	0x04

#endif
