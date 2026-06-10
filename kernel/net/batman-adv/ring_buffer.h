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
#ifndef _NET_BATMAN_ADV_RING_BUFFER_H_
#define _NET_BATMAN_ADV_RING_BUFFER_H_

void batadv_ring_buffer_set(uint8_t lq_recv[], uint8_t *lq_index,
			    uint8_t value);
uint8_t batadv_ring_buffer_avg(const uint8_t lq_recv[]);

#endif /* _NET_BATMAN_ADV_RING_BUFFER_H_ */
