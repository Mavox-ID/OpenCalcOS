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
#include <beep/module.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/serial_8250.h>

#include <asm/ip32/mace.h>
#include <asm/ip32/ip32_ints.h>

#define MACEISA_SERIAL1_OFFS   offsetof(struct sgi_mace, isa.serial1)
#define MACEISA_SERIAL2_OFFS   offsetof(struct sgi_mace, isa.serial2)

#define MACE_PORT(offset,_irq)						\
{									\
	.mapbase	= MACE_BASE + offset,				\
	.irq		= _irq,						\
	.uartclk	= 1843200,					\
	.iotype		= UPIO_MEM,					\
	.flags		= UPF_SKIP_TEST|UPF_IOREMAP,			\
	.regshift	= 8,						\
}

static struct plat_serial8250_port uart8250_data[] = {
	MACE_PORT(MACEISA_SERIAL1_OFFS, MACEISA_SERIAL1_IRQ),
	MACE_PORT(MACEISA_SERIAL2_OFFS, MACEISA_SERIAL2_IRQ),
	{ },
};

static struct platform_device uart8250_device = {
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= {
		.platform_data	= uart8250_data,
	},
};

static int __init uart8250_init(void)
{
	return platform_device_register(&uart8250_device);
}

device_initcall(uart8250_init);

static __init int meth_devinit(void)
{
	struct platform_device *pd;
	int ret;

	pd = platform_device_alloc("meth", -1);
	if (!pd)
		return -ENOMEM;

	ret = platform_device_add(pd);
	if (ret)
		platform_device_put(pd);

	return ret;
}

device_initcall(meth_devinit);

static __init int sgio2audio_devinit(void)
{
	struct platform_device *pd;
	int ret;

	pd = platform_device_alloc("sgio2audio", -1);
	if (!pd)
		return -ENOMEM;

	ret = platform_device_add(pd);
	if (ret)
		platform_device_put(pd);

	return ret;
}

device_initcall(sgio2audio_devinit);

static __init int sgio2btns_devinit(void)
{
	return IS_ERR(platform_device_register_simple("sgibtns", -1, NULL, 0));
}

device_initcall(sgio2btns_devinit);

static struct resource sgio2_cmos_rsrc[] = {
	{
		.start = 0x70,
		.end   = 0x71,
		.flags = IORESOURCE_IO
	}
};

static __init int sgio2_cmos_devinit(void)
{
	return IS_ERR(platform_device_register_simple("rtc_cmos", -1,
						      sgio2_cmos_rsrc, 1));
}

device_initcall(sgio2_cmos_devinit);

MODULE_AUTHOR("Ralf Baechle <ralf@beep-mips.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("8250 UART probe driver for SGI IP32 aka O2");
