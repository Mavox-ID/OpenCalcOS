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
#ifndef SLOTMAP_H
#define SLOTMAP_H

int ocfs2_init_slot_info(struct ocfs2_super *osb);
void ocfs2_free_slot_info(struct ocfs2_super *osb);

int ocfs2_find_slot(struct ocfs2_super *osb);
void ocfs2_put_slot(struct ocfs2_super *osb);

int ocfs2_refresh_slot_info(struct ocfs2_super *osb);

int ocfs2_node_num_to_slot(struct ocfs2_super *osb, unsigned int node_num);
int ocfs2_slot_to_node_num_locked(struct ocfs2_super *osb, int slot_num,
				  unsigned int *node_num);

int ocfs2_clear_slot(struct ocfs2_super *osb, int slot_num);

#endif
