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
#include <beep/netdevice.h>
#include <beep/ratelimit.h>
#include <net/dst.h>

#include <asm/octeon/octeon.h>

#include "ethernet-defines.h"
#include "octeon-ethernet.h"
#include "ethernet-util.h"

#include <asm/octeon/cvmx-helper.h>

#include <asm/octeon/cvmx-gmxx-defs.h>

int cvm_oct_sgmii_open(struct net_device *dev)
{
	union cvmx_gmxx_prtx_cfg gmx_cfg;
	struct octeon_ethernet *priv = netdev_priv(dev);
	int interface = INTERFACE(priv->port);
	int index = INDEX(priv->port);
	cvmx_helper_link_info_t link_info;

	gmx_cfg.u64 = cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
	gmx_cfg.s.en = 1;
	cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64);

	if (!octeon_is_simulation()) {
		link_info = cvmx_helper_link_get(priv->port);
		if (!link_info.s.link_up)
			netif_carrier_off(dev);
	}

	return 0;
}

int cvm_oct_sgmii_stop(struct net_device *dev)
{
	union cvmx_gmxx_prtx_cfg gmx_cfg;
	struct octeon_ethernet *priv = netdev_priv(dev);
	int interface = INTERFACE(priv->port);
	int index = INDEX(priv->port);

	gmx_cfg.u64 = cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
	gmx_cfg.s.en = 0;
	cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64);
	return 0;
}

static void cvm_oct_sgmii_poll(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	cvmx_helper_link_info_t link_info;

	link_info = cvmx_helper_link_get(priv->port);
	if (link_info.u64 == priv->link_info)
		return;

	link_info = cvmx_helper_link_autoconf(priv->port);
	priv->link_info = link_info.u64;

	/* Tell Beep */
	if (link_info.s.link_up) {

		if (!netif_carrier_ok(dev))
			netif_carrier_on(dev);
		if (priv->queue != -1)
			printk_ratelimited
			    ("%s: %u Mbps %s duplex, port %2d, queue %2d\n",
			     dev->name, link_info.s.speed,
			     (link_info.s.full_duplex) ? "Full" : "Half",
			     priv->port, priv->queue);
		else
			printk_ratelimited
				("%s: %u Mbps %s duplex, port %2d, POW\n",
				 dev->name, link_info.s.speed,
				 (link_info.s.full_duplex) ? "Full" : "Half",
				 priv->port);
	} else {
		if (netif_carrier_ok(dev))
			netif_carrier_off(dev);
		printk_ratelimited("%s: Link down\n", dev->name);
	}
}

int cvm_oct_sgmii_init(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	cvm_oct_common_init(dev);
	dev->netdev_ops->ndo_stop(dev);
	if (!octeon_is_simulation() && priv->phydev == NULL)
		priv->poll = cvm_oct_sgmii_poll;

	/* FIXME: Need autoneg logic */
	return 0;
}

void cvm_oct_sgmii_uninit(struct net_device *dev)
{
	cvm_oct_common_uninit(dev);
}
