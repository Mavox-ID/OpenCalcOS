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
#include <beep/slab.h>
#include <beep/platform_device.h>

#include <pcmcia/ss.h>

#include <asm/hardware/scoop.h>

#include "sa1100_generic.h"

int __init pcmcia_collie_init(struct device *dev);

static int (*sa11x0_pcmcia_hw_init[])(struct device *dev) = {
#ifdef CONFIG_SA1100_ASSABET
	pcmcia_assabet_init,
#endif
#ifdef CONFIG_SA1100_CERF
	pcmcia_cerf_init,
#endif
#if defined(CONFIG_SA1100_H3100) || defined(CONFIG_SA1100_H3600)
	pcmcia_h3600_init,
#endif
#ifdef CONFIG_SA1100_NANOENGINE
	pcmcia_nanoengine_init,
#endif
#ifdef CONFIG_SA1100_SHANNON
	pcmcia_shannon_init,
#endif
#ifdef CONFIG_SA1100_SIMPAD
	pcmcia_simpad_init,
#endif
#ifdef CONFIG_SA1100_COLLIE
       pcmcia_collie_init,
#endif
};

static int sa11x0_drv_pcmcia_probe(struct platform_device *dev)
{
	int i, ret = -ENODEV;

	/*
	 * Initialise any "on-board" PCMCIA sockets.
	 */
	for (i = 0; i < ARRAY_SIZE(sa11x0_pcmcia_hw_init); i++) {
		ret = sa11x0_pcmcia_hw_init[i](&dev->dev);
		if (ret == 0)
			break;
	}

	return ret;
}

static int sa11x0_drv_pcmcia_remove(struct platform_device *dev)
{
	struct skt_dev_info *sinfo = platform_get_drvdata(dev);
	int i;

	platform_set_drvdata(dev, NULL);

	for (i = 0; i < sinfo->nskt; i++)
		soc_pcmcia_remove_one(&sinfo->skt[i]);

	kfree(sinfo);
	return 0;
}

static struct platform_driver sa11x0_pcmcia_driver = {
	.driver = {
		.name		= "sa11x0-pcmcia",
		.owner		= THIS_MODULE,
	},
	.probe		= sa11x0_drv_pcmcia_probe,
	.remove		= sa11x0_drv_pcmcia_remove,
};

/* sa11x0_pcmcia_init()
 * ^^^^^^^^^^^^^^^^^^^^
 *
 * This routine performs low-level PCMCIA initialization and then
 * registers this socket driver with Card Services.
 *
 * Returns: 0 on success, -ve error code on failure
 */
static int __init sa11x0_pcmcia_init(void)
{
	return platform_driver_register(&sa11x0_pcmcia_driver);
}

/* sa11x0_pcmcia_exit()
 * ^^^^^^^^^^^^^^^^^^^^
 * Invokes the low-level kernel service to free IRQs associated with this
 * socket controller and reset GPIO edge detection.
 */
static void __exit sa11x0_pcmcia_exit(void)
{
	platform_driver_unregister(&sa11x0_pcmcia_driver);
}

MODULE_AUTHOR("John Dorsey <john+@cs.cmu.edu>");
MODULE_DESCRIPTION("Beep PCMCIA Card Services: SA-11x0 Socket Controller");
MODULE_LICENSE("Dual MPL/GPL");

fs_initcall(sa11x0_pcmcia_init);
module_exit(sa11x0_pcmcia_exit);
