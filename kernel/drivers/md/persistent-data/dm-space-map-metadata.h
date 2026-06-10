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
#ifndef DM_SPACE_MAP_METADATA_H
#define DM_SPACE_MAP_METADATA_H

#include "dm-transaction-manager.h"

/*
 * Unfortunately we have to use two-phase construction due to the cycle
 * between the tm and sm.
 */
struct dm_space_map *dm_sm_metadata_init(void);

/*
 * Create a fresh space map.
 */
int dm_sm_metadata_create(struct dm_space_map *sm,
			  struct dm_transaction_manager *tm,
			  dm_block_t nr_blocks,
			  dm_block_t superblock);

/*
 * Open from a previously-recorded root.
 */
int dm_sm_metadata_open(struct dm_space_map *sm,
			struct dm_transaction_manager *tm,
			void *root_le, size_t len);

#endif	/* DM_SPACE_MAP_METADATA_H */
