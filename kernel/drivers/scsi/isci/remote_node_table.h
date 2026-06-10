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
#ifndef _SCIC_SDS_REMOTE_NODE_TABLE_H_
#define _SCIC_SDS_REMOTE_NODE_TABLE_H_

#include "isci.h"

/**
 *
 *
 * Remote node sets are sets of remote node index in the remtoe node table The
 * SCU hardware requires that STP remote node entries take three consecutive
 * remote node index so the table is arranged in sets of three. The bits are
 * used as 0111 0111 to make a byte and the bits define the set of three remote
 * nodes to use as a sequence.
 */
#define SCIC_SDS_REMOTE_NODE_SETS_PER_BYTE 2

/**
 *
 *
 * Since the remote node table is organized as DWORDS take the remote node sets
 * in bytes and represent them in DWORDs. The lowest ordered bits are the ones
 * used in case full DWORD is not being used. i.e. 0000 0000 0000 0000 0111
 * 0111 0111 0111 // if only a single WORD is in use in the DWORD.
 */
#define SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD \
	(sizeof(u32) * SCIC_SDS_REMOTE_NODE_SETS_PER_BYTE)
/**
 *
 *
 * This is a count of the numeber of remote nodes that can be represented in a
 * byte
 */
#define SCIC_SDS_REMOTE_NODES_PER_BYTE	\
	(SCU_STP_REMOTE_NODE_COUNT * SCIC_SDS_REMOTE_NODE_SETS_PER_BYTE)

/**
 *
 *
 * This is a count of the number of remote nodes that can be represented in a
 * DWROD
 */
#define SCIC_SDS_REMOTE_NODES_PER_DWORD	\
	(sizeof(u32) * SCIC_SDS_REMOTE_NODES_PER_BYTE)

/**
 *
 *
 * This is the number of bits in a remote node group
 */
#define SCIC_SDS_REMOTE_NODES_BITS_PER_GROUP   4

#define SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX      (0xFFFFFFFF)
#define SCIC_SDS_REMOTE_NODE_TABLE_FULL_SLOT_VALUE    (0x07)
#define SCIC_SDS_REMOTE_NODE_TABLE_EMPTY_SLOT_VALUE   (0x00)

/**
 *
 *
 * Expander attached sata remote node count
 */
#define SCU_STP_REMOTE_NODE_COUNT        3

/**
 *
 *
 * Expander or direct attached ssp remote node count
 */
#define SCU_SSP_REMOTE_NODE_COUNT        1

/**
 *
 *
 * Direct attached STP remote node count
 */
#define SCU_SATA_REMOTE_NODE_COUNT       1

/**
 * struct sci_remote_node_table -
 *
 *
 */
struct sci_remote_node_table {
	/**
	 * This field contains the array size in dwords
	 */
	u16 available_nodes_array_size;

	/**
	 * This field contains the array size of the
	 */
	u16 group_array_size;

	/**
	 * This field is the array of available remote node entries in bits.
	 * Because of the way STP remote node data is allocated on the SCU hardware
	 * the remote nodes must occupy three consecutive remote node context
	 * entries.  For ease of allocation and de-allocation we have broken the
	 * sets of three into a single nibble.  When the STP RNi is allocated all
	 * of the bits in the nibble are cleared.  This math results in a table size
	 * of MAX_REMOTE_NODES / CONSECUTIVE RNi ENTRIES for STP / 2 entries per byte.
	 */
	u32 available_remote_nodes[
		(SCI_MAX_REMOTE_DEVICES / SCIC_SDS_REMOTE_NODES_PER_DWORD)
		+ ((SCI_MAX_REMOTE_DEVICES % SCIC_SDS_REMOTE_NODES_PER_DWORD) != 0)];

	/**
	 * This field is the nibble selector for the above table.  There are three
	 * possible selectors each for fast lookup when trying to find one, two or
	 * three remote node entries.
	 */
	u32 remote_node_groups[
		SCU_STP_REMOTE_NODE_COUNT][
		(SCI_MAX_REMOTE_DEVICES / (32 * SCU_STP_REMOTE_NODE_COUNT))
		+ ((SCI_MAX_REMOTE_DEVICES % (32 * SCU_STP_REMOTE_NODE_COUNT)) != 0)];

};

/* --------------------------------------------------------------------------- */

void sci_remote_node_table_initialize(
	struct sci_remote_node_table *remote_node_table,
	u32 remote_node_entries);

u16 sci_remote_node_table_allocate_remote_node(
	struct sci_remote_node_table *remote_node_table,
	u32 remote_node_count);

void sci_remote_node_table_release_remote_node_index(
	struct sci_remote_node_table *remote_node_table,
	u32 remote_node_count,
	u16 remote_node_index);

#endif /* _SCIC_SDS_REMOTE_NODE_TABLE_H_ */
