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
#ifndef __ASM_ARCH_OMAP_AMS_DELTA_H
#define __ASM_ARCH_OMAP_AMS_DELTA_H

#if defined (CONFIG_MACH_AMS_DELTA)

#define AMD_DELTA_LATCH2_SCARD_RSTIN	0x0400
#define AMD_DELTA_LATCH2_SCARD_CMDVCC	0x0800
#define AMS_DELTA_LATCH2_MODEM_CODEC	0x2000

#define AMS_DELTA_GPIO_PIN_KEYBRD_DATA	0
#define AMS_DELTA_GPIO_PIN_KEYBRD_CLK	1
#define AMS_DELTA_GPIO_PIN_MODEM_IRQ	2
#define AMS_DELTA_GPIO_PIN_HOOK_SWITCH	4
#define AMS_DELTA_GPIO_PIN_SCARD_NOFF	6
#define AMS_DELTA_GPIO_PIN_SCARD_IO	7
#define AMS_DELTA_GPIO_PIN_CONFIG	11
#define AMS_DELTA_GPIO_PIN_NAND_RB	12

#define AMS_DELTA_GPIO_PIN_LCD_VBLEN		240
#define AMS_DELTA_GPIO_PIN_LCD_NDISP		241
#define AMS_DELTA_GPIO_PIN_NAND_NCE		242
#define AMS_DELTA_GPIO_PIN_NAND_NRE		243
#define AMS_DELTA_GPIO_PIN_NAND_NWP		244
#define AMS_DELTA_GPIO_PIN_NAND_NWE		245
#define AMS_DELTA_GPIO_PIN_NAND_ALE		246
#define AMS_DELTA_GPIO_PIN_NAND_CLE		247
#define AMS_DELTA_GPIO_PIN_KEYBRD_PWR		248
#define AMS_DELTA_GPIO_PIN_KEYBRD_DATAOUT	249
#define AMS_DELTA_GPIO_PIN_SCARD_RSTIN		250
#define AMS_DELTA_GPIO_PIN_SCARD_CMDVCC		251
#define AMS_DELTA_GPIO_PIN_MODEM_NRESET		252
#define AMS_DELTA_GPIO_PIN_MODEM_CODEC		253

#define AMS_DELTA_LATCH2_GPIO_BASE	AMS_DELTA_GPIO_PIN_LCD_VBLEN
#define AMS_DELTA_LATCH2_NGPIO		16

#ifndef __ASSEMBLY__
void ams_delta_latch_write(int base, int ngpio, u16 mask, u16 value);
#define ams_delta_latch2_write(mask, value) \
	ams_delta_latch_write(AMS_DELTA_LATCH2_GPIO_BASE, \
			AMS_DELTA_LATCH2_NGPIO, (mask), (value))
#endif

#endif /* CONFIG_MACH_AMS_DELTA */

#endif /* __ASM_ARCH_OMAP_AMS_DELTA_H */
