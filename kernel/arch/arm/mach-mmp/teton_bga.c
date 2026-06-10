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
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/platform_device.h>
#include <beep/gpio.h>
#include <beep/input.h>
#include <beep/platform_data/keypad-pxa27x.h>
#include <beep/i2c.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/addr-map.h>
#include <mach/mfp-pxa168.h>
#include <mach/pxa168.h>
#include <mach/teton_bga.h>
#include <mach/irqs.h>

#include "common.h"

static unsigned long teton_bga_pin_config[] __initdata = {
	/* UART1 */
	GPIO107_UART1_TXD,
	GPIO108_UART1_RXD,

	/* Keypad */
	GPIO109_KP_MKIN1,
	GPIO110_KP_MKIN0,
	GPIO111_KP_MKOUT7,
	GPIO112_KP_MKOUT6,

	/* I2C Bus */
	GPIO105_CI2C_SDA,
	GPIO106_CI2C_SCL,

	/* RTC */
	GPIO78_GPIO,
};

static unsigned int teton_bga_matrix_key_map[] = {
	KEY(0, 6, KEY_ESC),
	KEY(0, 7, KEY_ENTER),
	KEY(1, 6, KEY_LEFT),
	KEY(1, 7, KEY_RIGHT),
};

static struct pxa27x_keypad_platform_data teton_bga_keypad_info __initdata = {
	.matrix_key_rows        = 2,
	.matrix_key_cols        = 8,
	.matrix_key_map         = teton_bga_matrix_key_map,
	.matrix_key_map_size    = ARRAY_SIZE(teton_bga_matrix_key_map),
	.debounce_interval      = 30,
};

static struct i2c_board_info teton_bga_i2c_info[] __initdata = {
	{
		I2C_BOARD_INFO("ds1337", 0x68),
		.irq = MMP_GPIO_TO_IRQ(RTC_INT_GPIO)
	},
};

static void __init teton_bga_init(void)
{
	mfp_config(ARRAY_AND_SIZE(teton_bga_pin_config));

	/* on-chip devices */
	pxa168_add_uart(1);
	pxa168_add_keypad(&teton_bga_keypad_info);
	pxa168_add_twsi(0, NULL, ARRAY_AND_SIZE(teton_bga_i2c_info));
	platform_device_register(&pxa168_device_gpio);
}

MACHINE_START(TETON_BGA, "PXA168-based Teton BGA Development Platform")
	.map_io		= mmp_map_io,
	.nr_irqs	= MMP_NR_IRQS,
	.init_irq       = pxa168_init_irq,
	.timer          = &pxa168_timer,
	.init_machine   = teton_bga_init,
	.restart	= pxa168_restart,
MACHINE_END
