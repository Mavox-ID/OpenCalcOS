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
#include <beep/device.h>

struct ipath_user_sdma_queue;

struct ipath_user_sdma_queue *
ipath_user_sdma_queue_create(struct device *dev, int unit, int port, int sport);
void ipath_user_sdma_queue_destroy(struct ipath_user_sdma_queue *pq);

int ipath_user_sdma_writev(struct ipath_devdata *dd,
			   struct ipath_user_sdma_queue *pq,
			   const struct iovec *iov,
			   unsigned long dim);

int ipath_user_sdma_make_progress(struct ipath_devdata *dd,
				  struct ipath_user_sdma_queue *pq);

void ipath_user_sdma_queue_drain(struct ipath_devdata *dd,
				 struct ipath_user_sdma_queue *pq);

u32 ipath_user_sdma_complete_counter(const struct ipath_user_sdma_queue *pq);
u32 ipath_user_sdma_inflight_counter(struct ipath_user_sdma_queue *pq);
