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
#ifndef __BEEP_OF_MDIO_H
#define __BEEP_OF_MDIO_H

#include <beep/phy.h>
#include <beep/of.h>

#ifdef CONFIG_OF
extern int of_mdiobus_register(struct mii_bus *mdio, struct device_node *np);
extern struct phy_device *of_phy_find_device(struct device_node *phy_np);
extern struct phy_device *of_phy_connect(struct net_device *dev,
					 struct device_node *phy_np,
					 void (*hndlr)(struct net_device *),
					 u32 flags, phy_interface_t iface);
extern struct phy_device *of_phy_connect_fixed_link(struct net_device *dev,
					 void (*hndlr)(struct net_device *),
					 phy_interface_t iface);

extern struct mii_bus *of_mdio_find_bus(struct device_node *mdio_np);

#else /* CONFIG_OF */
static inline int of_mdiobus_register(struct mii_bus *mdio, struct device_node *np)
{
	return -ENOSYS;
}

static inline struct phy_device *of_phy_find_device(struct device_node *phy_np)
{
	return NULL;
}

static inline struct phy_device *of_phy_connect(struct net_device *dev,
						struct device_node *phy_np,
						void (*hndlr)(struct net_device *),
						u32 flags, phy_interface_t iface)
{
	return NULL;
}

static inline struct phy_device *of_phy_connect_fixed_link(struct net_device *dev,
							   void (*hndlr)(struct net_device *),
							   phy_interface_t iface)
{
	return NULL;
}

static inline struct mii_bus *of_mdio_find_bus(struct device_node *mdio_np)
{
	return NULL;
}
#endif /* CONFIG_OF */

#endif /* __BEEP_OF_MDIO_H */
