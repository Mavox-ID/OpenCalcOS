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
#ifndef NSPIRE_MMIO_H
#define NSPIRE_MMIO_H

#include <asm-generic/sizes.h>

/*
	Memory map:
	0xFEE00000 - 0xFF000000		0x90000000 - 0x90200000		(APB)
	0xFEDFF000 - 0xFEE00000		0xDC000000 - 0xDC001000		(Interrupt Controller)
	0xFED7F000 - 0xFEDFF000		0x00000000 - 0x00080000		(Boot1 ROM)
	0xFED7E000 - 0xFED7F000		0xC4000000 - 0xC4001000		(ADC)
*/
#define NSPIRE_APB_PHYS_BASE		0x90000000
#define NSPIRE_APB_SIZE			SZ_2M
#define NSPIRE_APB_VIRT_BASE		0xFEE00000

#define NSPIRE_APB_PHYS(x)		((NSPIRE_APB_PHYS_BASE) + (x))
#define NSPIRE_APB_VIRT(x)		((NSPIRE_APB_VIRT_BASE) + (x))
#define NSPIRE_APB_VIRTIO(x)		IOMEM(NSPIRE_APB_VIRT(x))


#define NSPIRE_INTERRUPT_PHYS_BASE	0xDC000000
#define NSPIRE_INTERRUPT_SIZE		SZ_4K
#define NSPIRE_INTERRUPT_VIRT_BASE	0xFEDFF000

#define NSPIRE_LCD_PHYS_BASE		0xC0000000

#define NSPIRE_OTG_PHYS_BASE		0xB0000000
#define NSPIRE_OTG_SIZE			SZ_8K

#define NSPIRE_NAND_PHYS_BASE		0x81000000
#define NSPIRE_NAND_SIZE		SZ_16M

#define NSPIRE_BOOT1_PHYS_BASE		0x00000000
#define NSPIRE_BOOT1_SIZE		0x00080000
#define NSPIRE_BOOT1_VIRT_BASE		0xFED7F000

#define NSPIRE_APB_GPIO			0x00000
#define NSPIRE_APB_UART			0x20000
#define NSPIRE_APB_I2C			0x50000
#define NSPIRE_APB_WATCHDOG		0x60000
#define NSPIRE_APB_RTC			0x90000
#define NSPIRE_APB_MISC			0xA0000
#define NSPIRE_APB_POWER		0xB0000
#define NSPIRE_APB_TIMER2		0xD0000
#define NSPIRE_APB_KEYPAD		0xE0000
#define NSPIRE_APB_CONTRAST		0xF0000

#define NSPIRE_SRAM_PHYS_BASE		0xA4000000
#define NSPIRE_SRAM_SIZE		0x00020000

#define NSPIRE_ADC_PHYS_BASE		0xC4000000
#define NSPIRE_ADC_SIZE			SZ_4K
#define NSPIRE_ADC_VIRT_BASE		0xFED7E000

#endif
