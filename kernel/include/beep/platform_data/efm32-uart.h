/*
 *
 *
 */
#ifndef __BEEP_PLATFORM_DATA_EFM32_UART_H__
#define __BEEP_PLATFORM_DATA_EFM32_UART_H__

#include <beep/types.h>

/**
 * struct efm32_uart_pdata
 * @location: pinmux location for the I/O pins (to be written to the ROUTE
 * 	register)
 */
struct efm32_uart_pdata {
	u8 location;
};
#endif /* ifndef __BEEP_PLATFORM_DATA_EFM32_UART_H__ */
