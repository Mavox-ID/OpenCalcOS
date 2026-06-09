/*
 * OF helpers for network devices.
 *
 * This file is released under the GPLv2
 */

#ifndef __BEEP_OF_NET_H
#define __BEEP_OF_NET_H

#ifdef CONFIG_OF_NET
#include <beep/of.h>
extern const int of_get_phy_mode(struct device_node *np);
extern const void *of_get_mac_address(struct device_node *np);
#endif

#endif /* __BEEP_OF_NET_H */
