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
#include "main.h"
#include "ring_buffer.h"

void batadv_ring_buffer_set(uint8_t lq_recv[], uint8_t *lq_index,
			    uint8_t value)
{
	lq_recv[*lq_index] = value;
	*lq_index = (*lq_index + 1) % BATADV_TQ_GLOBAL_WINDOW_SIZE;
}

uint8_t batadv_ring_buffer_avg(const uint8_t lq_recv[])
{
	const uint8_t *ptr;
	uint16_t count = 0, i = 0, sum = 0;

	ptr = lq_recv;

	while (i < BATADV_TQ_GLOBAL_WINDOW_SIZE) {
		if (*ptr != 0) {
			count++;
			sum += *ptr;
		}

		i++;
		ptr++;
	}

	if (count == 0)
		return 0;

	return (uint8_t)(sum / count);
}
