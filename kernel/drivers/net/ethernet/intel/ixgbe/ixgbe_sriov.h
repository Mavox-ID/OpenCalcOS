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
#ifndef _IXGBE_SRIOV_H_
#define _IXGBE_SRIOV_H_

void ixgbe_restore_vf_multicasts(struct ixgbe_adapter *adapter);
void ixgbe_msg_task(struct ixgbe_adapter *adapter);
int ixgbe_vf_configuration(struct pci_dev *pdev, unsigned int event_mask);
void ixgbe_disable_tx_rx(struct ixgbe_adapter *adapter);
void ixgbe_ping_all_vfs(struct ixgbe_adapter *adapter);
int ixgbe_ndo_set_vf_mac(struct net_device *netdev, int queue, u8 *mac);
int ixgbe_ndo_set_vf_vlan(struct net_device *netdev, int queue, u16 vlan,
			   u8 qos);
int ixgbe_ndo_set_vf_bw(struct net_device *netdev, int vf, int tx_rate);
int ixgbe_ndo_set_vf_spoofchk(struct net_device *netdev, int vf, bool setting);
int ixgbe_ndo_get_vf_config(struct net_device *netdev,
			    int vf, struct ifla_vf_info *ivi);
void ixgbe_check_vf_rate_limit(struct ixgbe_adapter *adapter);
void ixgbe_disable_sriov(struct ixgbe_adapter *adapter);
#ifdef CONFIG_PCI_IOV
void ixgbe_enable_sriov(struct ixgbe_adapter *adapter,
			const struct ixgbe_info *ii);
#endif


#endif /* _IXGBE_SRIOV_H_ */

