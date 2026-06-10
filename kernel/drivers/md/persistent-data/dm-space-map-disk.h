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
#ifndef _BEEP_DM_SPACE_MAP_DISK_H
#define _BEEP_DM_SPACE_MAP_DISK_H

#include "dm-block-manager.h"

struct dm_space_map;
struct dm_transaction_manager;

/*
 * Unfortunately we have to use two-phase construction due to the cycle
 * between the tm and sm.
 */
struct dm_space_map *dm_sm_disk_create(struct dm_transaction_manager *tm,
				       dm_block_t nr_blocks);

struct dm_space_map *dm_sm_disk_open(struct dm_transaction_manager *tm,
				     void *root, size_t len);

#endif /* _BEEP_DM_SPACE_MAP_DISK_H */
