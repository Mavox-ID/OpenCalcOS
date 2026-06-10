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
#ifndef _NET_BATMAN_ADV_VIS_H_
#define _NET_BATMAN_ADV_VIS_H_

/* timeout of vis packets in milliseconds */
#define BATADV_VIS_TIMEOUT		200000

int batadv_vis_seq_print_text(struct seq_file *seq, void *offset);
void batadv_receive_server_sync_packet(struct batadv_priv *bat_priv,
				       struct batadv_vis_packet *vis_packet,
				       int vis_info_len);
void batadv_receive_client_update_packet(struct batadv_priv *bat_priv,
					 struct batadv_vis_packet *vis_packet,
					 int vis_info_len);
int batadv_vis_init(struct batadv_priv *bat_priv);
void batadv_vis_quit(struct batadv_priv *bat_priv);

#endif /* _NET_BATMAN_ADV_VIS_H_ */
