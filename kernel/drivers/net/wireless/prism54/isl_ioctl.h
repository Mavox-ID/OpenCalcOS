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
#ifndef _ISL_IOCTL_H
#define _ISL_IOCTL_H

#include "islpci_mgt.h"
#include "islpci_dev.h"

#include <net/iw_handler.h>	/* New driver API */

#define SUPPORTED_WIRELESS_EXT                  19

void prism54_mib_init(islpci_private *);

struct iw_statistics *prism54_get_wireless_stats(struct net_device *);
void prism54_update_stats(struct work_struct *);

void prism54_acl_init(struct islpci_acl *);
void prism54_acl_clean(struct islpci_acl *);

void prism54_process_trap(struct work_struct *);

void prism54_wpa_bss_ie_init(islpci_private *priv);
void prism54_wpa_bss_ie_clean(islpci_private *priv);

int prism54_set_mac_address(struct net_device *, void *);

extern const struct iw_handler_def prism54_handler_def;

#endif				/* _ISL_IOCTL_H */
