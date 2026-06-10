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
#ifndef __IPZ_PT_FN_H__
#define __IPZ_PT_FN_H__

#define EHCA_PAGESHIFT   12
#define EHCA_PAGESIZE   4096UL
#define EHCA_PAGEMASK   (~(EHCA_PAGESIZE-1))
#define EHCA_PT_ENTRIES 512UL

#include "ehca_tools.h"
#include "ehca_qes.h"

struct ehca_pd;
struct ipz_small_queue_page;

extern struct kmem_cache *small_qp_cache;

/* struct generic ehca page */
struct ipz_page {
	u8 entries[EHCA_PAGESIZE];
};

#define IPZ_SPAGE_PER_KPAGE (PAGE_SIZE / 512)

struct ipz_small_queue_page {
	unsigned long page;
	unsigned long bitmap[IPZ_SPAGE_PER_KPAGE / BITS_PER_LONG];
	int fill;
	void *mapped_addr;
	u32 mmap_count;
	struct list_head list;
};

/* struct generic queue in beep kernel virtual memory (kv) */
struct ipz_queue {
	u64 current_q_offset;	/* current queue entry */

	struct ipz_page **queue_pages;	/* array of pages belonging to queue */
	u32 qe_size;		/* queue entry size */
	u32 act_nr_of_sg;
	u32 queue_length;	/* queue length allocated in bytes */
	u32 pagesize;
	u32 toggle_state;	/* toggle flag - per page */
	u32 offset; /* save offset within page for small_qp */
	struct ipz_small_queue_page *small_page;
};

/*
 * return current Queue Entry for a certain q_offset
 * returns address (kv) of Queue Entry
 */
static inline void *ipz_qeit_calc(struct ipz_queue *queue, u64 q_offset)
{
	struct ipz_page *current_page;
	if (q_offset >= queue->queue_length)
		return NULL;
	current_page = (queue->queue_pages)[q_offset >> EHCA_PAGESHIFT];
	return &current_page->entries[q_offset & (EHCA_PAGESIZE - 1)];
}

/*
 * return current Queue Entry
 * returns address (kv) of Queue Entry
 */
static inline void *ipz_qeit_get(struct ipz_queue *queue)
{
	return ipz_qeit_calc(queue, queue->current_q_offset);
}

/*
 * return current Queue Page , increment Queue Page iterator from
 * page to page in struct ipz_queue, last increment will return 0! and
 * NOT wrap
 * returns address (kv) of Queue Page
 * warning don't use in parallel with ipz_QE_get_inc()
 */
void *ipz_qpageit_get_inc(struct ipz_queue *queue);

/*
 * return current Queue Entry, increment Queue Entry iterator by one
 * step in struct ipz_queue, will wrap in ringbuffer
 * returns address (kv) of Queue Entry BEFORE increment
 * warning don't use in parallel with ipz_qpageit_get_inc()
 */
static inline void *ipz_qeit_get_inc(struct ipz_queue *queue)
{
	void *ret = ipz_qeit_get(queue);
	queue->current_q_offset += queue->qe_size;
	if (queue->current_q_offset >= queue->queue_length) {
		queue->current_q_offset = 0;
		/* toggle the valid flag */
		queue->toggle_state = (~queue->toggle_state) & 1;
	}

	return ret;
}

/*
 * return a bool indicating whether current Queue Entry is valid
 */
static inline int ipz_qeit_is_valid(struct ipz_queue *queue)
{
	struct ehca_cqe *cqe = ipz_qeit_get(queue);
	return ((cqe->cqe_flags >> 7) == (queue->toggle_state & 1));
}

/*
 * return current Queue Entry, increment Queue Entry iterator by one
 * step in struct ipz_queue, will wrap in ringbuffer
 * returns address (kv) of Queue Entry BEFORE increment
 * returns 0 and does not increment, if wrong valid state
 * warning don't use in parallel with ipz_qpageit_get_inc()
 */
static inline void *ipz_qeit_get_inc_valid(struct ipz_queue *queue)
{
	return ipz_qeit_is_valid(queue) ? ipz_qeit_get_inc(queue) : NULL;
}

/*
 * returns and resets Queue Entry iterator
 * returns address (kv) of first Queue Entry
 */
static inline void *ipz_qeit_reset(struct ipz_queue *queue)
{
	queue->current_q_offset = 0;
	return ipz_qeit_get(queue);
}

/*
 * return the q_offset corresponding to an absolute address
 */
int ipz_queue_abs_to_offset(struct ipz_queue *queue, u64 addr, u64 *q_offset);

/*
 * return the next queue offset. don't modify the queue.
 */
static inline u64 ipz_queue_advance_offset(struct ipz_queue *queue, u64 offset)
{
	offset += queue->qe_size;
	if (offset >= queue->queue_length) offset = 0;
	return offset;
}

/* struct generic page table */
struct ipz_pt {
	u64 entries[EHCA_PT_ENTRIES];
};

/* struct page table for a queue, only to be used in pf */
struct ipz_qpt {
	/* queue page tables (kv), use u64 because we know the element length */
	u64 *qpts;
	u32 n_qpts;
	u32 n_ptes;       /*  number of page table entries */
	u64 *current_pte_addr;
};

/*
 * constructor for a ipz_queue_t, placement new for ipz_queue_t,
 * new for all dependent datastructors
 * all QP Tables are the same
 * flow:
 *    allocate+pin queue
 * see ipz_qpt_ctor()
 * returns true if ok, false if out of memory
 */
int ipz_queue_ctor(struct ehca_pd *pd, struct ipz_queue *queue,
		   const u32 nr_of_pages, const u32 pagesize,
		   const u32 qe_size, const u32 nr_of_sg,
		   int is_small);

/*
 * destructor for a ipz_queue_t
 *  -# free queue
 *  see ipz_queue_ctor()
 *  returns true if ok, false if queue was NULL-ptr of free failed
 */
int ipz_queue_dtor(struct ehca_pd *pd, struct ipz_queue *queue);

/*
 * constructor for a ipz_qpt_t,
 * placement new for struct ipz_queue, new for all dependent datastructors
 * all QP Tables are the same,
 * flow:
 * -# allocate+pin queue
 * -# initialise ptcb
 * -# allocate+pin PTs
 * -# link PTs to a ring, according to HCA Arch, set bit62 id needed
 * -# the ring must have room for exactly nr_of_PTEs
 * see ipz_qpt_ctor()
 */
void ipz_qpt_ctor(struct ipz_qpt *qpt,
		  const u32 nr_of_qes,
		  const u32 pagesize,
		  const u32 qe_size,
		  const u8 lowbyte, const u8 toggle,
		  u32 * act_nr_of_QEs, u32 * act_nr_of_pages);

/*
 * return current Queue Entry, increment Queue Entry iterator by one
 * step in struct ipz_queue, will wrap in ringbuffer
 * returns address (kv) of Queue Entry BEFORE increment
 * warning don't use in parallel with ipz_qpageit_get_inc()
 * warning unpredictable results may occur if steps>act_nr_of_queue_entries
 * fix EQ page problems
 */
void *ipz_qeit_eq_get_inc(struct ipz_queue *queue);

/*
 * return current Event Queue Entry, increment Queue Entry iterator
 * by one step in struct ipz_queue if valid, will wrap in ringbuffer
 * returns address (kv) of Queue Entry BEFORE increment
 * returns 0 and does not increment, if wrong valid state
 * warning don't use in parallel with ipz_queue_QPageit_get_inc()
 * warning unpredictable results may occur if steps>act_nr_of_queue_entries
 */
static inline void *ipz_eqit_eq_get_inc_valid(struct ipz_queue *queue)
{
	void *ret = ipz_qeit_get(queue);
	u32 qe = *(u8 *)ret;
	if ((qe >> 7) != (queue->toggle_state & 1))
		return NULL;
	ipz_qeit_eq_get_inc(queue); /* this is a good one */
	return ret;
}

static inline void *ipz_eqit_eq_peek_valid(struct ipz_queue *queue)
{
	void *ret = ipz_qeit_get(queue);
	u32 qe = *(u8 *)ret;
	if ((qe >> 7) != (queue->toggle_state & 1))
		return NULL;
	return ret;
}

/* returns address (GX) of first queue entry */
static inline u64 ipz_qpt_get_firstpage(struct ipz_qpt *qpt)
{
	return be64_to_cpu(qpt->qpts[0]);
}

/* returns address (kv) of first page of queue page table */
static inline void *ipz_qpt_get_qpt(struct ipz_qpt *qpt)
{
	return qpt->qpts;
}

#endif				/* __IPZ_PT_FN_H__ */
