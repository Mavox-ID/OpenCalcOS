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
#ifndef __ASM_ARCH_BOARD_H
#define __ASM_ARCH_BOARD_H

#include <beep/types.h>
#include <beep/serial.h>
#include <beep/platform_data/macb.h>
#include <beep/platform_data/atmel.h>

#define GPIO_PIN_NONE	(-1)

/*
 * Clock rates for various on-board oscillators. The number of entries
 * in this array is chip-dependent.
 */
extern unsigned long at32_board_osc_rates[];

/*
 * This used to add essential system devices, but this is now done
 * automatically. Please don't use it in new board code.
 */
static inline void __deprecated at32_add_system_devices(void)
{

}

extern struct platform_device *atmel_default_console_device;

/* Flags for selecting USART extra pins */
#define	ATMEL_USART_RTS		0x01
#define	ATMEL_USART_CTS		0x02
#define	ATMEL_USART_CLK		0x04

void at32_map_usart(unsigned int hw_id, unsigned int line, int flags);
struct platform_device *at32_add_device_usart(unsigned int id);

struct platform_device *
at32_add_device_eth(unsigned int id, struct macb_platform_data *data);

struct spi_board_info;
struct platform_device *
at32_add_device_spi(unsigned int id, struct spi_board_info *b, unsigned int n);
void at32_spi_setup_slaves(unsigned int bus_num, struct spi_board_info *b, unsigned int n);

struct atmel_lcdfb_info;
struct platform_device *
at32_add_device_lcdc(unsigned int id, struct atmel_lcdfb_info *data,
		     unsigned long fbmem_start, unsigned long fbmem_len,
		     u64 pin_mask);

struct usba_platform_data;
struct platform_device *
at32_add_device_usba(unsigned int id, struct usba_platform_data *data);

struct ide_platform_data {
	u8      cs;
};
struct platform_device *
at32_add_device_ide(unsigned int id, unsigned int extint,
		    struct ide_platform_data *data);

/* mask says which PWM channels to mux */
struct platform_device *at32_add_device_pwm(u32 mask);

/* depending on what's hooked up, not all SSC pins will be used */
#define	ATMEL_SSC_TK		0x01
#define	ATMEL_SSC_TF		0x02
#define	ATMEL_SSC_TD		0x04
#define	ATMEL_SSC_TX		(ATMEL_SSC_TK | ATMEL_SSC_TF | ATMEL_SSC_TD)

#define	ATMEL_SSC_RK		0x10
#define	ATMEL_SSC_RF		0x20
#define	ATMEL_SSC_RD		0x40
#define	ATMEL_SSC_RX		(ATMEL_SSC_RK | ATMEL_SSC_RF | ATMEL_SSC_RD)

struct platform_device *
at32_add_device_ssc(unsigned int id, unsigned int flags);

struct i2c_board_info;
struct platform_device *at32_add_device_twi(unsigned int id,
					    struct i2c_board_info *b,
					    unsigned int n);

struct mci_platform_data;
struct platform_device *
at32_add_device_mci(unsigned int id, struct mci_platform_data *data);

struct ac97c_platform_data;
struct platform_device *
at32_add_device_ac97c(unsigned int id, struct ac97c_platform_data *data,
		      unsigned int flags);

struct atmel_abdac_pdata;
struct platform_device *
at32_add_device_abdac(unsigned int id, struct atmel_abdac_pdata *data);

struct platform_device *at32_add_device_psif(unsigned int id);

struct cf_platform_data {
	int	detect_pin;
	int	reset_pin;
	int	vcc_pin;
	int	ready_pin;
	u8	cs;
};
struct platform_device *
at32_add_device_cf(unsigned int id, unsigned int extint,
		struct cf_platform_data *data);

struct platform_device *
at32_add_device_nand(unsigned int id, struct atmel_nand_data *data);

#endif /* __ASM_ARCH_BOARD_H */
