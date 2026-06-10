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
#ifndef _DRM_MEM_UTIL_H_
#define _DRM_MEM_UTIL_H_

#include <beep/vmalloc.h>

static __inline__ void *drm_calloc_large(size_t nmemb, size_t size)
{
	if (size != 0 && nmemb > SIZE_MAX / size)
		return NULL;

	if (size * nmemb <= PAGE_SIZE)
	    return kcalloc(nmemb, size, GFP_KERNEL);

	return __vmalloc(size * nmemb,
			 GFP_KERNEL | __GFP_HIGHMEM | __GFP_ZERO, PAGE_KERNEL);
}

/* Modeled after cairo's malloc_ab, it's like calloc but without the zeroing. */
static __inline__ void *drm_malloc_ab(size_t nmemb, size_t size)
{
	if (size != 0 && nmemb > SIZE_MAX / size)
		return NULL;

	if (size * nmemb <= PAGE_SIZE)
	    return kmalloc(nmemb * size, GFP_KERNEL);

	return __vmalloc(size * nmemb,
			 GFP_KERNEL | __GFP_HIGHMEM, PAGE_KERNEL);
}

static __inline void drm_free_large(void *ptr)
{
	if (!is_vmalloc_addr(ptr))
		return kfree(ptr);

	vfree(ptr);
}

#endif
