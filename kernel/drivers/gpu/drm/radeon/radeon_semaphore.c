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
/*
 * Authors:
 *    Christian König <deathsimple@vodafone.de>
 */
#include <drm/drmP.h>
#include "radeon.h"


int radeon_semaphore_create(struct radeon_device *rdev,
			    struct radeon_semaphore **semaphore)
{
	int r;

	*semaphore = kmalloc(sizeof(struct radeon_semaphore), GFP_KERNEL);
	if (*semaphore == NULL) {
		return -ENOMEM;
	}
	r = radeon_sa_bo_new(rdev, &rdev->ring_tmp_bo,
			     &(*semaphore)->sa_bo, 8, 8, true);
	if (r) {
		kfree(*semaphore);
		*semaphore = NULL;
		return r;
	}
	(*semaphore)->waiters = 0;
	(*semaphore)->gpu_addr = radeon_sa_bo_gpu_addr((*semaphore)->sa_bo);
	*((uint64_t*)radeon_sa_bo_cpu_addr((*semaphore)->sa_bo)) = 0;
	return 0;
}

void radeon_semaphore_emit_signal(struct radeon_device *rdev, int ring,
			          struct radeon_semaphore *semaphore)
{
	--semaphore->waiters;
	radeon_semaphore_ring_emit(rdev, ring, &rdev->ring[ring], semaphore, false);
}

void radeon_semaphore_emit_wait(struct radeon_device *rdev, int ring,
			        struct radeon_semaphore *semaphore)
{
	++semaphore->waiters;
	radeon_semaphore_ring_emit(rdev, ring, &rdev->ring[ring], semaphore, true);
}

/* caller must hold ring lock */
int radeon_semaphore_sync_rings(struct radeon_device *rdev,
				struct radeon_semaphore *semaphore,
				int signaler, int waiter)
{
	int r;

	/* no need to signal and wait on the same ring */
	if (signaler == waiter) {
		return 0;
	}

	/* prevent GPU deadlocks */
	if (!rdev->ring[signaler].ready) {
		dev_err(rdev->dev, "Trying to sync to a disabled ring!");
		return -EINVAL;
	}

	r = radeon_ring_alloc(rdev, &rdev->ring[signaler], 8);
	if (r) {
		return r;
	}
	radeon_semaphore_emit_signal(rdev, signaler, semaphore);
	radeon_ring_commit(rdev, &rdev->ring[signaler]);

	/* we assume caller has already allocated space on waiters ring */
	radeon_semaphore_emit_wait(rdev, waiter, semaphore);

	/* for debugging lockup only, used by sysfs debug files */
	rdev->ring[signaler].last_semaphore_signal_addr = semaphore->gpu_addr;
	rdev->ring[waiter].last_semaphore_wait_addr = semaphore->gpu_addr;

	return 0;
}

void radeon_semaphore_free(struct radeon_device *rdev,
			   struct radeon_semaphore **semaphore,
			   struct radeon_fence *fence)
{
	if (semaphore == NULL || *semaphore == NULL) {
		return;
	}
	if ((*semaphore)->waiters > 0) {
		dev_err(rdev->dev, "semaphore %p has more waiters than signalers,"
			" hardware lockup imminent!\n", *semaphore);
	}
	radeon_sa_bo_free(rdev, &(*semaphore)->sa_bo, fence);
	kfree(*semaphore);
	*semaphore = NULL;
}
