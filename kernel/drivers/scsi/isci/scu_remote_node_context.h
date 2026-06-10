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
#ifndef __SCU_REMOTE_NODE_CONTEXT_HEADER__
#define __SCU_REMOTE_NODE_CONTEXT_HEADER__

/**
 * This file contains the structures and constatns used by the SCU hardware to
 *    describe a remote node context.
 *
 *
 */

/**
 * struct ssp_remote_node_context - This structure contains the SCU hardware
 *    definition for an SSP remote node.
 *
 *
 */
struct ssp_remote_node_context {
	/* WORD 0 */

	/**
	 * This field is the remote node index assigned for this remote node. All
	 * remote nodes must have a unique remote node index. The value of the remote
	 * node index can not exceed the maximum number of remote nodes reported in
	 * the SCU device context capacity register.
	 */
	u32 remote_node_index:12;
	u32 reserved0_1:4;

	/**
	 * This field tells the SCU hardware how many simultaneous connections that
	 * this remote node will support.
	 */
	u32 remote_node_port_width:4;

	/**
	 * This field tells the SCU hardware which logical port to associate with this
	 * remote node.
	 */
	u32 logical_port_index:3;
	u32 reserved0_2:5;

	/**
	 * This field will enable the I_T nexus loss timer for this remote node.
	 */
	u32 nexus_loss_timer_enable:1;

	/**
	 * This field is the for driver debug only and is not used.
	 */
	u32 check_bit:1;

	/**
	 * This field must be set to true when the hardware DMAs the remote node
	 * context to the hardware SRAM.  When the remote node is being invalidated
	 * this field must be set to false.
	 */
	u32 is_valid:1;

	/**
	 * This field must be set to true.
	 */
	u32 is_remote_node_context:1;

	/* WORD 1 - 2 */

	/**
	 * This is the low word of the remote device SAS Address
	 */
	u32 remote_sas_address_lo;

	/**
	 * This field is the high word of the remote device SAS Address
	 */
	u32 remote_sas_address_hi;

	/* WORD 3 */
	/**
	 * This field reprensets the function number assigned to this remote device.
	 * This value must match the virtual function number that is being used to
	 * communicate to the device.
	 */
	u32 function_number:8;
	u32 reserved3_1:8;

	/**
	 * This field provides the driver a way to cheat on the arbitration wait time
	 * for this remote node.
	 */
	u32 arbitration_wait_time:16;

	/* WORD 4 */
	/**
	 * This field tells the SCU hardware how long this device may occupy the
	 * connection before it must be closed.
	 */
	u32 connection_occupancy_timeout:16;

	/**
	 * This field tells the SCU hardware how long to maintain a connection when
	 * there are no frames being transmitted on the link.
	 */
	u32 connection_inactivity_timeout:16;

	/* WORD  5 */
	/**
	 * This field allows the driver to cheat on the arbitration wait time for this
	 * remote node.
	 */
	u32 initial_arbitration_wait_time:16;

	/**
	 * This field is tells the hardware what to program for the connection rate in
	 * the open address frame.  See the SAS spec for valid values.
	 */
	u32 oaf_connection_rate:4;

	/**
	 * This field tells the SCU hardware what to program for the features in the
	 * open address frame.  See the SAS spec for valid values.
	 */
	u32 oaf_features:4;

	/**
	 * This field tells the SCU hardware what to use for the source zone group in
	 * the open address frame.  See the SAS spec for more details on zoning.
	 */
	u32 oaf_source_zone_group:8;

	/* WORD 6 */
	/**
	 * This field tells the SCU hardware what to use as the more capibilities in
	 * the open address frame. See the SAS Spec for details.
	 */
	u32 oaf_more_compatibility_features;

	/* WORD 7 */
	u32 reserved7;

};

/**
 * struct stp_remote_node_context - This structure contains the SCU hardware
 *    definition for a STP remote node.
 *
 * STP Targets are not yet supported so this definition is a placeholder until
 * we do support them.
 */
struct stp_remote_node_context {
	/**
	 * Placeholder data for the STP remote node.
	 */
	u32 data[8];

};

/**
 * This union combines the SAS and SATA remote node definitions.
 *
 * union scu_remote_node_context
 */
union scu_remote_node_context {
	/**
	 * SSP Remote Node
	 */
	struct ssp_remote_node_context ssp;

	/**
	 * STP Remote Node
	 */
	struct stp_remote_node_context stp;

};

#endif /* __SCU_REMOTE_NODE_CONTEXT_HEADER__ */
