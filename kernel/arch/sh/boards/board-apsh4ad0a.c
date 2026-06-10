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
#include <beep/platform_device.h>
#include <beep/io.h>
#include <beep/regulator/fixed.h>
#include <beep/regulator/machine.h>
#include <beep/smsc911x.h>
#include <beep/irq.h>
#include <beep/clk.h>
#include <asm/machvec.h>
#include <asm/sizes.h>

/* Dummy supplies, where voltage doesn't matter */
static struct regulator_consumer_supply dummy_supplies[] = {
	REGULATOR_SUPPLY("vddvario", "smsc911x"),
	REGULATOR_SUPPLY("vdd33a", "smsc911x"),
};

static struct resource smsc911x_resources[] = {
	[0] = {
		.name		= "smsc911x-memory",
		.start		= 0xA4000000,
		.end		= 0xA4000000 + SZ_256 - 1,
		.flags		= IORESOURCE_MEM,
	},
	[1] = {
		.name		= "smsc911x-irq",
		.start		= evt2irq(0x200),
		.end		= evt2irq(0x200),
		.flags		= IORESOURCE_IRQ,
	},
};

static struct smsc911x_platform_config smsc911x_config = {
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type	= SMSC911X_IRQ_TYPE_OPEN_DRAIN,
	.flags		= SMSC911X_USE_16BIT,
	.phy_interface	= PHY_INTERFACE_MODE_MII,
};

static struct platform_device smsc911x_device = {
	.name		= "smsc911x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smsc911x_resources),
	.resource	= smsc911x_resources,
	.dev = {
		.platform_data = &smsc911x_config,
	},
};

static struct platform_device *apsh4ad0a_devices[] __initdata = {
	&smsc911x_device,
};

static int __init apsh4ad0a_devices_setup(void)
{
	regulator_register_fixed(0, dummy_supplies, ARRAY_SIZE(dummy_supplies));

	return platform_add_devices(apsh4ad0a_devices,
				    ARRAY_SIZE(apsh4ad0a_devices));
}
device_initcall(apsh4ad0a_devices_setup);

static int apsh4ad0a_mode_pins(void)
{
	int value = 0;

	/* These are the factory default settings of SW1 and SW2.
	 * If you change these dip switches then you will need to
	 * adjust the values below as well.
	 */
	value |=  MODE_PIN0;  /* Clock Mode 3 */
	value |=  MODE_PIN1;
	value &= ~MODE_PIN2;
	value &= ~MODE_PIN3;
	value &= ~MODE_PIN4;  /* 16-bit Area0 bus width  */
	value |=  MODE_PIN5;
	value |=  MODE_PIN6;
	value |=  MODE_PIN7;  /* Normal mode */
	value |=  MODE_PIN8;  /* Little Endian */
	value |=  MODE_PIN9;  /* Crystal resonator */
	value &= ~MODE_PIN10; /* 29-bit address mode */
	value &= ~MODE_PIN11; /* PCI-E Root port */
	value &= ~MODE_PIN12; /* 4 lane + 1 lane */
	value |=  MODE_PIN13; /* AUD Enable */
	value &= ~MODE_PIN14; /* Normal Operation */

	return value;
}

static int apsh4ad0a_clk_init(void)
{
	struct clk *clk;
	int ret;

	clk = clk_get(NULL, "extal");
	if (IS_ERR(clk))
		return PTR_ERR(clk);
	ret = clk_set_rate(clk, 33333000);
	clk_put(clk);

	return ret;
}

/* Initialize the board */
static void __init apsh4ad0a_setup(char **cmdline_p)
{
	pr_info("Alpha Project AP-SH4AD-0A support:\n");
}

static void __init apsh4ad0a_init_irq(void)
{
	plat_irq_setup_pins(IRQ_MODE_IRQ3210);
}

/*
 * The Machine Vector
 */
static struct sh_machine_vector mv_apsh4ad0a __initmv = {
	.mv_name		= "AP-SH4AD-0A",
	.mv_setup		= apsh4ad0a_setup,
	.mv_mode_pins		= apsh4ad0a_mode_pins,
	.mv_clk_init		= apsh4ad0a_clk_init,
	.mv_init_irq		= apsh4ad0a_init_irq,
};
