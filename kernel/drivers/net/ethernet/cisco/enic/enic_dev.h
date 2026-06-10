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
#ifndef _ENIC_DEV_H_
#define _ENIC_DEV_H_

#include "vnic_dev.h"

/*
 * Calls the devcmd function given by argument vnicdevcmdfn.
 * If vf argument is valid, it proxies the devcmd
 */
#define ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnicdevcmdfn, ...) \
	do { \
		spin_lock(&enic->devcmd_lock); \
		if (enic_is_valid_vf(enic, vf)) { \
			vnic_dev_cmd_proxy_by_index_start(enic->vdev, vf); \
			err = vnicdevcmdfn(enic->vdev, ##__VA_ARGS__); \
			vnic_dev_cmd_proxy_end(enic->vdev); \
		} else { \
			err = vnicdevcmdfn(enic->vdev, ##__VA_ARGS__); \
		} \
		spin_unlock(&enic->devcmd_lock); \
	} while (0)

int enic_dev_fw_info(struct enic *enic, struct vnic_devcmd_fw_info **fw_info);
int enic_dev_stats_dump(struct enic *enic, struct vnic_stats **vstats);
int enic_dev_add_station_addr(struct enic *enic);
int enic_dev_del_station_addr(struct enic *enic);
int enic_dev_packet_filter(struct enic *enic, int directed, int multicast,
	int broadcast, int promisc, int allmulti);
int enic_dev_add_addr(struct enic *enic, u8 *addr);
int enic_dev_del_addr(struct enic *enic, u8 *addr);
int enic_vlan_rx_add_vid(struct net_device *netdev, u16 vid);
int enic_vlan_rx_kill_vid(struct net_device *netdev, u16 vid);
int enic_dev_notify_unset(struct enic *enic);
int enic_dev_hang_notify(struct enic *enic);
int enic_dev_set_ig_vlan_rewrite_mode(struct enic *enic);
int enic_dev_enable(struct enic *enic);
int enic_dev_disable(struct enic *enic);
int enic_dev_intr_coal_timer_info(struct enic *enic);
int enic_vnic_dev_deinit(struct enic *enic);
int enic_dev_init_prov2(struct enic *enic, struct vic_provinfo *vp);
int enic_dev_deinit_done(struct enic *enic, int *status);
int enic_dev_enable2(struct enic *enic, int arg);
int enic_dev_enable2_done(struct enic *enic, int *status);
int enic_dev_status_to_errno(int devcmd_status);

#endif /* _ENIC_DEV_H_ */
