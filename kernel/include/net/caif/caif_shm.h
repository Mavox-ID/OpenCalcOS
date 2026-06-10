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
#ifndef CAIF_SHM_H_
#define CAIF_SHM_H_

struct shmdev_layer {
	u32 shm_base_addr;
	u32 shm_total_sz;
	u32 shm_id;
	u32 shm_loopback;
	void *hmbx;
	int (*pshmdev_mbxsend) (u32 shm_id, u32 mbx_msg);
	int (*pshmdev_mbxsetup) (void *pshmdrv_cb,
				struct shmdev_layer *pshm_dev, void *pshm_drv);
	struct net_device *pshm_netdev;
};

extern int caif_shmcore_probe(struct shmdev_layer *pshm_dev);
extern void caif_shmcore_remove(struct net_device *pshm_netdev);

#endif
