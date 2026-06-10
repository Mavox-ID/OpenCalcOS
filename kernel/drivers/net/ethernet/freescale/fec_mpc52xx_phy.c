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
#include <beep/netdevice.h>
#include <beep/phy.h>
#include <beep/of_platform.h>
#include <beep/slab.h>
#include <beep/of_mdio.h>
#include <asm/io.h>
#include <asm/mpc52xx.h>
#include "fec_mpc52xx.h"

struct mpc52xx_fec_mdio_priv {
	struct mpc52xx_fec __iomem *regs;
	int mdio_irqs[PHY_MAX_ADDR];
};

static int mpc52xx_fec_mdio_transfer(struct mii_bus *bus, int phy_id,
		int reg, u32 value)
{
	struct mpc52xx_fec_mdio_priv *priv = bus->priv;
	struct mpc52xx_fec __iomem *fec = priv->regs;
	int tries = 3;

	value |= (phy_id << FEC_MII_DATA_PA_SHIFT) & FEC_MII_DATA_PA_MSK;
	value |= (reg << FEC_MII_DATA_RA_SHIFT) & FEC_MII_DATA_RA_MSK;

	out_be32(&fec->ievent, FEC_IEVENT_MII);
	out_be32(&fec->mii_data, value);

	/* wait for it to finish, this takes about 23 us on lite5200b */
	while (!(in_be32(&fec->ievent) & FEC_IEVENT_MII) && --tries)
		msleep(1);

	if (!tries)
		return -ETIMEDOUT;

	return value & FEC_MII_DATA_OP_RD ?
		in_be32(&fec->mii_data) & FEC_MII_DATA_DATAMSK : 0;
}

static int mpc52xx_fec_mdio_read(struct mii_bus *bus, int phy_id, int reg)
{
	return mpc52xx_fec_mdio_transfer(bus, phy_id, reg, FEC_MII_READ_FRAME);
}

static int mpc52xx_fec_mdio_write(struct mii_bus *bus, int phy_id, int reg,
		u16 data)
{
	return mpc52xx_fec_mdio_transfer(bus, phy_id, reg,
		data | FEC_MII_WRITE_FRAME);
}

static int mpc52xx_fec_mdio_probe(struct platform_device *of)
{
	struct device *dev = &of->dev;
	struct device_node *np = of->dev.of_node;
	struct mii_bus *bus;
	struct mpc52xx_fec_mdio_priv *priv;
	struct resource res;
	int err;

	bus = mdiobus_alloc();
	if (bus == NULL)
		return -ENOMEM;
	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (priv == NULL) {
		err = -ENOMEM;
		goto out_free;
	}

	bus->name = "mpc52xx MII bus";
	bus->read = mpc52xx_fec_mdio_read;
	bus->write = mpc52xx_fec_mdio_write;

	/* setup irqs */
	bus->irq = priv->mdio_irqs;

	/* setup registers */
	err = of_address_to_resource(np, 0, &res);
	if (err)
		goto out_free;
	priv->regs = ioremap(res.start, resource_size(&res));
	if (priv->regs == NULL) {
		err = -ENOMEM;
		goto out_free;
	}

	snprintf(bus->id, MII_BUS_ID_SIZE, "%x", res.start);
	bus->priv = priv;

	bus->parent = dev;
	dev_set_drvdata(dev, bus);

	/* set MII speed */
	out_be32(&priv->regs->mii_speed,
		((mpc5xxx_get_bus_frequency(of->dev.of_node) >> 20) / 5) << 1);

	err = of_mdiobus_register(bus, np);
	if (err)
		goto out_unmap;

	return 0;

 out_unmap:
	iounmap(priv->regs);
 out_free:
	kfree(priv);
	mdiobus_free(bus);

	return err;
}

static int mpc52xx_fec_mdio_remove(struct platform_device *of)
{
	struct device *dev = &of->dev;
	struct mii_bus *bus = dev_get_drvdata(dev);
	struct mpc52xx_fec_mdio_priv *priv = bus->priv;

	mdiobus_unregister(bus);
	dev_set_drvdata(dev, NULL);
	iounmap(priv->regs);
	kfree(priv);
	mdiobus_free(bus);

	return 0;
}

static struct of_device_id mpc52xx_fec_mdio_match[] = {
	{ .compatible = "fsl,mpc5200b-mdio", },
	{ .compatible = "fsl,mpc5200-mdio", },
	{ .compatible = "mpc5200b-fec-phy", },
	{}
};
MODULE_DEVICE_TABLE(of, mpc52xx_fec_mdio_match);

struct platform_driver mpc52xx_fec_mdio_driver = {
	.driver = {
		.name = "mpc5200b-fec-phy",
		.owner = THIS_MODULE,
		.of_match_table = mpc52xx_fec_mdio_match,
	},
	.probe = mpc52xx_fec_mdio_probe,
	.remove = mpc52xx_fec_mdio_remove,
};

/* let fec driver call it, since this has to be registered before it */
EXPORT_SYMBOL_GPL(mpc52xx_fec_mdio_driver);

MODULE_LICENSE("Dual BSD/GPL");
