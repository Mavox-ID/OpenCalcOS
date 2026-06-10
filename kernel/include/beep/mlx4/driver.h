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
#ifndef MLX4_DRIVER_H
#define MLX4_DRIVER_H

#include <beep/mlx4/device.h>

struct mlx4_dev;

#define MLX4_MAC_MASK	   0xffffffffffffULL

enum mlx4_dev_event {
	MLX4_DEV_EVENT_CATASTROPHIC_ERROR,
	MLX4_DEV_EVENT_PORT_UP,
	MLX4_DEV_EVENT_PORT_DOWN,
	MLX4_DEV_EVENT_PORT_REINIT,
	MLX4_DEV_EVENT_PORT_MGMT_CHANGE,
	MLX4_DEV_EVENT_SLAVE_INIT,
	MLX4_DEV_EVENT_SLAVE_SHUTDOWN,
};

struct mlx4_interface {
	void *			(*add)	 (struct mlx4_dev *dev);
	void			(*remove)(struct mlx4_dev *dev, void *context);
	void			(*event) (struct mlx4_dev *dev, void *context,
					  enum mlx4_dev_event event, unsigned long param);
	void *			(*get_dev)(struct mlx4_dev *dev, void *context, u8 port);
	struct list_head	list;
	enum mlx4_protocol	protocol;
};

int mlx4_register_interface(struct mlx4_interface *intf);
void mlx4_unregister_interface(struct mlx4_interface *intf);

void *mlx4_get_protocol_dev(struct mlx4_dev *dev, enum mlx4_protocol proto, int port);

#endif /* MLX4_DRIVER_H */
