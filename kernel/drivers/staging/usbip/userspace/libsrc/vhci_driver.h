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
#ifndef __VHCI_DRIVER_H
#define __VHCI_DRIVER_H

#include <sysfs/libsysfs.h>
#include <stdint.h>

#include "usbip_common.h"

#define USBIP_VHCI_BUS_TYPE "platform"
#define MAXNPORT 128

struct usbip_class_device {
	char class_path[SYSFS_PATH_MAX];
	char dev_path[SYSFS_PATH_MAX];
};

struct usbip_imported_device {
	uint8_t port;
	uint32_t status;

	uint32_t devid;

	uint8_t busnum;
	uint8_t devnum;

	/* usbip_class_device list */
	struct dlist *cdev_list;
	struct usbip_usb_device udev;
};

struct usbip_vhci_driver {
	char sysfs_mntpath[SYSFS_PATH_MAX];

	/* /sys/devices/platform/vhci_hcd */
	struct sysfs_device *hc_device;

	/* usbip_class_device list */
	struct dlist *cdev_list;

	int nports;
	struct usbip_imported_device idev[MAXNPORT];
};


extern struct usbip_vhci_driver *vhci_driver;

int usbip_vhci_driver_open(void);
void usbip_vhci_driver_close(void);

int  usbip_vhci_refresh_device_list(void);


int usbip_vhci_get_free_port(void);
int usbip_vhci_attach_device2(uint8_t port, int sockfd, uint32_t devid,
		uint32_t speed);

/* will be removed */
int usbip_vhci_attach_device(uint8_t port, int sockfd, uint8_t busnum,
		uint8_t devnum, uint32_t speed);

int usbip_vhci_detach_device(uint8_t port);

#endif /* __VHCI_DRIVER_H */
