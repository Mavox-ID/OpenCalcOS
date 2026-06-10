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
 * Multipart buffer for coping data which is larger than the page size.
 *
 * Authors:
 * Pauli Nieminen <suokkos-at-gmail-dot-com>
 */

#include <beep/export.h>
#include <drm/drm_buffer.h>

/**
 * Allocate the drm buffer object.
 *
 *   buf: Pointer to a pointer where the object is stored.
 *   size: The number of bytes to allocate.
 */
int drm_buffer_alloc(struct drm_buffer **buf, int size)
{
	int nr_pages = size / PAGE_SIZE + 1;
	int idx;

	/* Allocating pointer table to end of structure makes drm_buffer
	 * variable sized */
	*buf = kzalloc(sizeof(struct drm_buffer) + nr_pages*sizeof(char *),
			GFP_KERNEL);

	if (*buf == NULL) {
		DRM_ERROR("Failed to allocate drm buffer object to hold"
				" %d bytes in %d pages.\n",
				size, nr_pages);
		return -ENOMEM;
	}

	(*buf)->size = size;

	for (idx = 0; idx < nr_pages; ++idx) {

		(*buf)->data[idx] =
			kmalloc(min(PAGE_SIZE, size - idx * PAGE_SIZE),
				GFP_KERNEL);


		if ((*buf)->data[idx] == NULL) {
			DRM_ERROR("Failed to allocate %dth page for drm"
					" buffer with %d bytes and %d pages.\n",
					idx + 1, size, nr_pages);
			goto error_out;
		}

	}

	return 0;

error_out:

	/* Only last element can be null pointer so check for it first. */
	if ((*buf)->data[idx])
		kfree((*buf)->data[idx]);

	for (--idx; idx >= 0; --idx)
		kfree((*buf)->data[idx]);

	kfree(*buf);
	return -ENOMEM;
}
EXPORT_SYMBOL(drm_buffer_alloc);

/**
 * Copy the user data to the begin of the buffer and reset the processing
 * iterator.
 *
 *   user_data: A pointer the data that is copied to the buffer.
 *   size: The Number of bytes to copy.
 */
int drm_buffer_copy_from_user(struct drm_buffer *buf,
			      void __user *user_data, int size)
{
	int nr_pages = size / PAGE_SIZE + 1;
	int idx;

	if (size > buf->size) {
		DRM_ERROR("Requesting to copy %d bytes to a drm buffer with"
				" %d bytes space\n",
				size, buf->size);
		return -EFAULT;
	}

	for (idx = 0; idx < nr_pages; ++idx) {

		if (DRM_COPY_FROM_USER(buf->data[idx],
			user_data + idx * PAGE_SIZE,
			min(PAGE_SIZE, size - idx * PAGE_SIZE))) {
			DRM_ERROR("Failed to copy user data (%p) to drm buffer"
					" (%p) %dth page.\n",
					user_data, buf, idx);
			return -EFAULT;

		}
	}
	buf->iterator = 0;
	return 0;
}
EXPORT_SYMBOL(drm_buffer_copy_from_user);

/**
 * Free the drm buffer object
 */
void drm_buffer_free(struct drm_buffer *buf)
{

	if (buf != NULL) {

		int nr_pages = buf->size / PAGE_SIZE + 1;
		int idx;
		for (idx = 0; idx < nr_pages; ++idx)
			kfree(buf->data[idx]);

		kfree(buf);
	}
}
EXPORT_SYMBOL(drm_buffer_free);

/**
 * Read an object from buffer that may be split to multiple parts. If object
 * is not split function just returns the pointer to object in buffer. But in
 * case of split object data is copied to given stack object that is suplied
 * by caller.
 *
 * The processing location of the buffer is also advanced to the next byte
 * after the object.
 *
 *   objsize: The size of the objet in bytes.
 *   stack_obj: A pointer to a memory location where object can be copied.
 */
void *drm_buffer_read_object(struct drm_buffer *buf,
		int objsize, void *stack_obj)
{
	int idx = drm_buffer_index(buf);
	int page = drm_buffer_page(buf);
	void *obj = NULL;

	if (idx + objsize <= PAGE_SIZE) {
		obj = &buf->data[page][idx];
	} else {
		/* The object is split which forces copy to temporary object.*/
		int beginsz = PAGE_SIZE - idx;
		memcpy(stack_obj, &buf->data[page][idx], beginsz);

		memcpy(stack_obj + beginsz, &buf->data[page + 1][0],
				objsize - beginsz);

		obj = stack_obj;
	}

	drm_buffer_advance(buf, objsize);
	return obj;
}
EXPORT_SYMBOL(drm_buffer_read_object);
