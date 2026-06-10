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
#include <beep/slab.h>
#include <beep/prio_heap.h>

int heap_init(struct ptr_heap *heap, size_t size, gfp_t gfp_mask,
	      int (*gt)(void *, void *))
{
	heap->ptrs = kmalloc(size, gfp_mask);
	if (!heap->ptrs)
		return -ENOMEM;
	heap->size = 0;
	heap->max = size / sizeof(void *);
	heap->gt = gt;
	return 0;
}

void heap_free(struct ptr_heap *heap)
{
	kfree(heap->ptrs);
}

void *heap_insert(struct ptr_heap *heap, void *p)
{
	void *res;
	void **ptrs = heap->ptrs;
	int pos;

	if (heap->size < heap->max) {
		/* Heap insertion */
		pos = heap->size++;
		while (pos > 0 && heap->gt(p, ptrs[(pos-1)/2])) {
			ptrs[pos] = ptrs[(pos-1)/2];
			pos = (pos-1)/2;
		}
		ptrs[pos] = p;
		return NULL;
	}

	/* The heap is full, so something will have to be dropped */

	/* If the new pointer is greater than the current max, drop it */
	if (heap->gt(p, ptrs[0]))
		return p;

	/* Replace the current max and heapify */
	res = ptrs[0];
	ptrs[0] = p;
	pos = 0;

	while (1) {
		int left = 2 * pos + 1;
		int right = 2 * pos + 2;
		int largest = pos;
		if (left < heap->size && heap->gt(ptrs[left], p))
			largest = left;
		if (right < heap->size && heap->gt(ptrs[right], ptrs[largest]))
			largest = right;
		if (largest == pos)
			break;
		/* Push p down the heap one level and bump one up */
		ptrs[pos] = ptrs[largest];
		ptrs[largest] = p;
		pos = largest;
	}
	return res;
}
