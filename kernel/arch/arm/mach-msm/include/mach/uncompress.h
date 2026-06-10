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
#ifndef __ASM_ARCH_MSM_UNCOMPRESS_H
#define __ASM_ARCH_MSM_UNCOMPRESS_H

#include <asm/barrier.h>
#include <asm/processor.h>
#include <mach/msm_iomap.h>

#define UART_CSR      (*(volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x08))
#define UART_TF       (*(volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x0c))

#define UART_DM_SR    (*((volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x08)))
#define UART_DM_CR    (*((volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x10)))
#define UART_DM_ISR   (*((volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x14)))
#define UART_DM_NCHAR (*((volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x40)))
#define UART_DM_TF    (*((volatile uint32_t *)(MSM_DEBUG_UART_PHYS + 0x70)))

static void putc(int c)
{
#if defined(MSM_DEBUG_UART_PHYS)
#ifdef CONFIG_MSM_HAS_DEBUG_UART_HS
	/*
	 * Wait for TX_READY to be set; but skip it if we have a
	 * TX underrun.
	 */
	if (UART_DM_SR & 0x08)
		while (!(UART_DM_ISR & 0x80))
			cpu_relax();

	UART_DM_CR = 0x300;
	UART_DM_NCHAR = 0x1;
	UART_DM_TF = c;
#else
	while (!(UART_CSR & 0x04))
		cpu_relax();
	UART_TF = c;
#endif
#endif
}

static inline void flush(void)
{
}

static inline void arch_decomp_setup(void)
{
}

static inline void arch_decomp_wdog(void)
{
}

#endif
