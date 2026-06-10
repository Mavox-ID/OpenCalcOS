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
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/delay.h>
#include <beep/init.h>
#include <beep/dmi.h>
#include <beep/io.h>

int io_delay_type __read_mostly = CONFIG_DEFAULT_IO_DELAY_TYPE;

static int __initdata io_delay_override;

/*
 * Paravirt wants native_io_delay to be a constant.
 */
void native_io_delay(void)
{
	switch (io_delay_type) {
	default:
	case CONFIG_IO_DELAY_TYPE_0X80:
		asm volatile ("outb %al, $0x80");
		break;
	case CONFIG_IO_DELAY_TYPE_0XED:
		asm volatile ("outb %al, $0xed");
		break;
	case CONFIG_IO_DELAY_TYPE_UDELAY:
		/*
		 * 2 usecs is an upper-bound for the outb delay but
		 * note that udelay doesn't have the bus-level
		 * side-effects that outb does, nor does udelay() have
		 * precise timings during very early bootup (the delays
		 * are shorter until calibrated):
		 */
		udelay(2);
	case CONFIG_IO_DELAY_TYPE_NONE:
		break;
	}
}
EXPORT_SYMBOL(native_io_delay);

static int __init dmi_io_delay_0xed_port(const struct dmi_system_id *id)
{
	if (io_delay_type == CONFIG_IO_DELAY_TYPE_0X80) {
		pr_notice("%s: using 0xed I/O delay port\n", id->ident);
		io_delay_type = CONFIG_IO_DELAY_TYPE_0XED;
	}

	return 0;
}

/*
 * Quirk table for systems that misbehave (lock up, etc.) if port
 * 0x80 is used:
 */
static struct dmi_system_id __initdata io_delay_0xed_port_dmi_table[] = {
	{
		.callback	= dmi_io_delay_0xed_port,
		.ident		= "Compaq Presario V6000",
		.matches	= {
			DMI_MATCH(DMI_BOARD_VENDOR,	"Quanta"),
			DMI_MATCH(DMI_BOARD_NAME,	"30B7")
		}
	},
	{
		.callback	= dmi_io_delay_0xed_port,
		.ident		= "HP Pavilion dv9000z",
		.matches	= {
			DMI_MATCH(DMI_BOARD_VENDOR,	"Quanta"),
			DMI_MATCH(DMI_BOARD_NAME,	"30B9")
		}
	},
	{
		.callback	= dmi_io_delay_0xed_port,
		.ident		= "HP Pavilion dv6000",
		.matches	= {
			DMI_MATCH(DMI_BOARD_VENDOR,	"Quanta"),
			DMI_MATCH(DMI_BOARD_NAME,	"30B8")
		}
	},
	{
		.callback	= dmi_io_delay_0xed_port,
		.ident		= "HP Pavilion tx1000",
		.matches	= {
			DMI_MATCH(DMI_BOARD_VENDOR,	"Quanta"),
			DMI_MATCH(DMI_BOARD_NAME,	"30BF")
		}
	},
	{
		.callback	= dmi_io_delay_0xed_port,
		.ident		= "Presario F700",
		.matches	= {
			DMI_MATCH(DMI_BOARD_VENDOR,	"Quanta"),
			DMI_MATCH(DMI_BOARD_NAME,	"30D3")
		}
	},
	{ }
};

void __init io_delay_init(void)
{
	if (!io_delay_override)
		dmi_check_system(io_delay_0xed_port_dmi_table);
}

static int __init io_delay_param(char *s)
{
	if (!s)
		return -EINVAL;

	if (!strcmp(s, "0x80"))
		io_delay_type = CONFIG_IO_DELAY_TYPE_0X80;
	else if (!strcmp(s, "0xed"))
		io_delay_type = CONFIG_IO_DELAY_TYPE_0XED;
	else if (!strcmp(s, "udelay"))
		io_delay_type = CONFIG_IO_DELAY_TYPE_UDELAY;
	else if (!strcmp(s, "none"))
		io_delay_type = CONFIG_IO_DELAY_TYPE_NONE;
	else
		return -EINVAL;

	io_delay_override = 1;
	return 0;
}

early_param("io_delay", io_delay_param);
