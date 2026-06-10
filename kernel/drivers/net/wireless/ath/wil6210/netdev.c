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
#include <beep/netdevice.h>
#include <beep/etherdevice.h>
#include <beep/slab.h>

#include "wil6210.h"

static int wil_open(struct net_device *ndev)
{
	struct wil6210_priv *wil = ndev_to_wil(ndev);

	return wil_up(wil);
}

static int wil_stop(struct net_device *ndev)
{
	struct wil6210_priv *wil = ndev_to_wil(ndev);

	return wil_down(wil);
}

/*
 * AC to queue mapping
 *
 * AC_VO -> queue 3
 * AC_VI -> queue 2
 * AC_BE -> queue 1
 * AC_BK -> queue 0
 */
static u16 wil_select_queue(struct net_device *ndev, struct sk_buff *skb)
{
	static const u16 wil_1d_to_queue[8] = { 1, 0, 0, 1, 2, 2, 3, 3 };
	struct wil6210_priv *wil = ndev_to_wil(ndev);
	u16 rc;

	skb->priority = cfg80211_classify8021d(skb);

	rc = wil_1d_to_queue[skb->priority];

	wil_dbg_TXRX(wil, "%s() %d -> %d\n", __func__, (int)skb->priority,
		     (int)rc);

	return rc;
}

static const struct net_device_ops wil_netdev_ops = {
	.ndo_open		= wil_open,
	.ndo_stop		= wil_stop,
	.ndo_start_xmit		= wil_start_xmit,
	.ndo_select_queue	= wil_select_queue,
	.ndo_set_mac_address    = eth_mac_addr,
	.ndo_validate_addr      = eth_validate_addr,
};

void *wil_if_alloc(struct device *dev, void __iomem *csr)
{
	struct net_device *ndev;
	struct wireless_dev *wdev;
	struct wil6210_priv *wil;
	struct ieee80211_channel *ch;
	int rc = 0;

	wdev = wil_cfg80211_init(dev);
	if (IS_ERR(wdev)) {
		dev_err(dev, "wil_cfg80211_init failed\n");
		return wdev;
	}

	wil = wdev_to_wil(wdev);
	wil->csr = csr;
	wil->wdev = wdev;

	rc = wil_priv_init(wil);
	if (rc) {
		dev_err(dev, "wil_priv_init failed\n");
		goto out_wdev;
	}

	wdev->iftype = NL80211_IFTYPE_STATION; /* TODO */
	/* default monitor channel */
	ch = wdev->wiphy->bands[IEEE80211_BAND_60GHZ]->channels;
	cfg80211_chandef_create(&wdev->preset_chandef, ch, NL80211_CHAN_NO_HT);

	ndev = alloc_netdev_mqs(0, "wlan%d", ether_setup, WIL6210_TX_QUEUES, 1);
	if (!ndev) {
		dev_err(dev, "alloc_netdev_mqs failed\n");
		rc = -ENOMEM;
		goto out_priv;
	}

	ndev->netdev_ops = &wil_netdev_ops;
	ndev->ieee80211_ptr = wdev;
	SET_NETDEV_DEV(ndev, wiphy_dev(wdev->wiphy));
	wdev->netdev = ndev;

	wil_link_off(wil);

	return wil;

 out_priv:
	wil_priv_deinit(wil);

 out_wdev:
	wil_wdev_free(wil);

	return ERR_PTR(rc);
}

void wil_if_free(struct wil6210_priv *wil)
{
	struct net_device *ndev = wil_to_ndev(wil);
	if (!ndev)
		return;

	free_netdev(ndev);
	wil_priv_deinit(wil);
	wil_wdev_free(wil);
}

int wil_if_add(struct wil6210_priv *wil)
{
	struct net_device *ndev = wil_to_ndev(wil);
	int rc;

	rc = register_netdev(ndev);
	if (rc < 0) {
		dev_err(&ndev->dev, "Failed to register netdev: %d\n", rc);
		return rc;
	}

	wil_link_off(wil);

	return 0;
}

void wil_if_remove(struct wil6210_priv *wil)
{
	struct net_device *ndev = wil_to_ndev(wil);

	unregister_netdev(ndev);
}
