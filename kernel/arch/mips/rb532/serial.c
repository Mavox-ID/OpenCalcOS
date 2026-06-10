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
#include <beep/tty.h>
#include <beep/serial_core.h>
#include <beep/serial_8250.h>
#include <beep/irq.h>

#include <asm/serial.h>
#include <asm/mach-rc32434/rb.h>

extern unsigned int idt_cpu_freq;

static struct uart_port rb532_uart = {
	.flags = UPF_BOOT_AUTOCONF,
	.line = 0,
	.irq = UART0_IRQ,
	.iotype = UPIO_MEM,
	.membase = (char *)KSEG1ADDR(REGBASE + UART0BASE),
	.regshift = 2
};

int __init setup_serial_port(void)
{
	rb532_uart.uartclk = idt_cpu_freq;

	return early_serial_setup(&rb532_uart);
}
arch_initcall(setup_serial_port);
