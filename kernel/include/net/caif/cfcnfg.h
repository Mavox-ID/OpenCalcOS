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
#ifndef CFCNFG_H_
#define CFCNFG_H_
#include <beep/spinlock.h>
#include <beep/netdevice.h>
#include <net/caif/caif_layer.h>
#include <net/caif/cfctrl.h>

struct cfcnfg;

/**
 * enum cfcnfg_phy_preference - Physical preference HW Abstraction
 *
 * @CFPHYPREF_UNSPECIFIED:	Default physical interface
 *
 * @CFPHYPREF_LOW_LAT:		Default physical interface for low-latency
 *				traffic
 * @CFPHYPREF_HIGH_BW:		Default physical interface for high-bandwidth
 *				traffic
 * @CFPHYPREF_LOOP:		TEST only Loopback interface simulating modem
 *				responses.
 *
 */
enum cfcnfg_phy_preference {
	CFPHYPREF_UNSPECIFIED,
	CFPHYPREF_LOW_LAT,
	CFPHYPREF_HIGH_BW,
	CFPHYPREF_LOOP
};

/**
 * cfcnfg_create() - Get the CAIF configuration object given network.
 * @net:	Network for the CAIF configuration object.
 */
struct cfcnfg *get_cfcnfg(struct net *net);

/**
 * cfcnfg_create() - Create the CAIF configuration object.
 */
struct cfcnfg *cfcnfg_create(void);

/**
 * cfcnfg_remove() -  Remove the CFCNFG object
 * @cfg: config object
 */
void cfcnfg_remove(struct cfcnfg *cfg);

/**
 * cfcnfg_add_phy_layer() - Adds a physical layer to the CAIF stack.
 * @cnfg:	Pointer to a CAIF configuration object, created by
 *		cfcnfg_create().
 * @dev:	Pointer to link layer device
 * @phy_layer:	Specify the physical layer. The transmit function
 *		MUST be set in the structure.
 * @pref:	The phy (link layer) preference.
 * @link_support: Protocol implementation for link layer specific protocol.
 * @fcs:	Specify if checksum is used in CAIF Framing Layer.
 * @head_room:	Head space needed by link specific protocol.
 */
void
cfcnfg_add_phy_layer(struct cfcnfg *cnfg,
		     struct net_device *dev, struct cflayer *phy_layer,
		     enum cfcnfg_phy_preference pref,
		     struct cflayer *link_support,
		     bool fcs, int head_room);

/**
 * cfcnfg_del_phy_layer - Deletes an phy layer from the CAIF stack.
 *
 * @cnfg:	Pointer to a CAIF configuration object, created by
 *		cfcnfg_create().
 * @phy_layer:	Adaptation layer to be removed.
 */
int cfcnfg_del_phy_layer(struct cfcnfg *cnfg, struct cflayer *phy_layer);

/**
 * cfcnfg_set_phy_state() - Set the state of the physical interface device.
 * @cnfg:	Configuration object
 * @phy_layer:	Physical Layer representation
 * @up:	State of device
 */
int cfcnfg_set_phy_state(struct cfcnfg *cnfg, struct cflayer *phy_layer,
				bool up);

#endif				/* CFCNFG_H_ */
