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
#include <beep/netdevice.h>
#include <beep/ethtool.h>
#include <beep/delay.h>

#include "rtl_core.h"

static void rtl819x_ethtool_get_drvinfo(struct net_device *dev,
		struct ethtool_drvinfo *info)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	strcpy(info->driver, DRV_NAME);
	strcpy(info->version, DRV_VERSION);
	strcpy(info->bus_info, pci_name(priv->pdev));
}

static u32 rtl819x_ethtool_get_link(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	return ((priv->rtllib->state == RTLLIB_LINKED) ||
		(priv->rtllib->state == RTLLIB_LINKED_SCANNING));
}

const struct ethtool_ops rtl819x_ethtool_ops = {
	.get_drvinfo = rtl819x_ethtool_get_drvinfo,
	.get_link = rtl819x_ethtool_get_link,
};
