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
#ifndef OCFS2_HEARTBEAT_H
#define OCFS2_HEARTBEAT_H

void ocfs2_init_node_maps(struct ocfs2_super *osb);

void ocfs2_do_node_down(int node_num, void *data);

/* node map functions - used to keep track of mounted and in-recovery
 * nodes. */
void ocfs2_node_map_set_bit(struct ocfs2_super *osb,
			    struct ocfs2_node_map *map,
			    int bit);
void ocfs2_node_map_clear_bit(struct ocfs2_super *osb,
			      struct ocfs2_node_map *map,
			      int bit);
int ocfs2_node_map_test_bit(struct ocfs2_super *osb,
			    struct ocfs2_node_map *map,
			    int bit);

#endif /* OCFS2_HEARTBEAT_H */
