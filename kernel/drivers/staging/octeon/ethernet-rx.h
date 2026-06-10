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
#include <asm/octeon/cvmx-fau.h>

void cvm_oct_poll_controller(struct net_device *dev);
void cvm_oct_rx_initialize(void);
void cvm_oct_rx_shutdown(void);

static inline void cvm_oct_rx_refill_pool(int fill_threshold)
{
	int number_to_free;
	int num_freed;
	/* Refill the packet buffer pool */
	number_to_free =
		cvmx_fau_fetch_and_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE, 0);

	if (number_to_free > fill_threshold) {
		cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE,
				      -number_to_free);
		num_freed = cvm_oct_mem_fill_fpa(CVMX_FPA_PACKET_POOL,
						 CVMX_FPA_PACKET_POOL_SIZE,
						 number_to_free);
		if (num_freed != number_to_free) {
			cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE,
					number_to_free - num_freed);
		}
	}
}
