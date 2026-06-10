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

#ifndef _DRM_BUFFER_H_
#define _DRM_BUFFER_H_

#include <drm/drmP.h>

struct drm_buffer {
	int iterator;
	int size;
	char *data[];
};


/**
 * Return the index of page that buffer is currently pointing at.
 */
static inline int drm_buffer_page(struct drm_buffer *buf)
{
	return buf->iterator / PAGE_SIZE;
}
/**
 * Return the index of the current byte in the page
 */
static inline int drm_buffer_index(struct drm_buffer *buf)
{
	return buf->iterator & (PAGE_SIZE - 1);
}
/**
 * Return number of bytes that is left to process
 */
static inline int drm_buffer_unprocessed(struct drm_buffer *buf)
{
	return buf->size - buf->iterator;
}

/**
 * Advance the buffer iterator number of bytes that is given.
 */
static inline void drm_buffer_advance(struct drm_buffer *buf, int bytes)
{
	buf->iterator += bytes;
}

/**
 * Allocate the drm buffer object.
 *
 *   buf: A pointer to a pointer where the object is stored.
 *   size: The number of bytes to allocate.
 */
extern int drm_buffer_alloc(struct drm_buffer **buf, int size);

/**
 * Copy the user data to the begin of the buffer and reset the processing
 * iterator.
 *
 *   user_data: A pointer the data that is copied to the buffer.
 *   size: The Number of bytes to copy.
 */
extern int drm_buffer_copy_from_user(struct drm_buffer *buf,
		void __user *user_data, int size);

/**
 * Free the drm buffer object
 */
extern void drm_buffer_free(struct drm_buffer *buf);

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
extern void *drm_buffer_read_object(struct drm_buffer *buf,
		int objsize, void *stack_obj);

/**
 * Returns the pointer to the dword which is offset number of elements from the
 * current processing location.
 *
 * Caller must make sure that dword is not split in the buffer. This
 * requirement is easily met if all the sizes of objects in buffer are
 * multiples of dword and PAGE_SIZE is multiple dword.
 *
 * Call to this function doesn't change the processing location.
 *
 *   offset: The index of the dword relative to the internat iterator.
 */
static inline void *drm_buffer_pointer_to_dword(struct drm_buffer *buffer,
		int offset)
{
	int iter = buffer->iterator + offset * 4;
	return &buffer->data[iter / PAGE_SIZE][iter & (PAGE_SIZE - 1)];
}
/**
 * Returns the pointer to the dword which is offset number of elements from
 * the current processing location.
 *
 * Call to this function doesn't change the processing location.
 *
 *   offset: The index of the byte relative to the internat iterator.
 */
static inline void *drm_buffer_pointer_to_byte(struct drm_buffer *buffer,
		int offset)
{
	int iter = buffer->iterator + offset;
	return &buffer->data[iter / PAGE_SIZE][iter & (PAGE_SIZE - 1)];
}

#endif
