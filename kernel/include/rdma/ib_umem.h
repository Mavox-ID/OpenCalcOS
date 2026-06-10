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
#ifndef IB_UMEM_H
#define IB_UMEM_H

#include <beep/list.h>
#include <beep/scatterlist.h>
#include <beep/workqueue.h>

struct ib_ucontext;

struct ib_umem {
	struct ib_ucontext     *context;
	size_t			length;
	int			offset;
	int			page_size;
	int                     writable;
	int                     hugetlb;
	struct list_head	chunk_list;
	struct work_struct	work;
	struct mm_struct       *mm;
	unsigned long		diff;
};

struct ib_umem_chunk {
	struct list_head	list;
	int                     nents;
	int                     nmap;
	struct scatterlist      page_list[0];
};

#ifdef CONFIG_INFINIBAND_USER_MEM

struct ib_umem *ib_umem_get(struct ib_ucontext *context, unsigned long addr,
			    size_t size, int access, int dmasync);
void ib_umem_release(struct ib_umem *umem);
int ib_umem_page_count(struct ib_umem *umem);

#else /* CONFIG_INFINIBAND_USER_MEM */

#include <beep/err.h>

static inline struct ib_umem *ib_umem_get(struct ib_ucontext *context,
					  unsigned long addr, size_t size,
					  int access, int dmasync) {
	return ERR_PTR(-EINVAL);
}
static inline void ib_umem_release(struct ib_umem *umem) { }
static inline int ib_umem_page_count(struct ib_umem *umem) { return 0; }

#endif /* CONFIG_INFINIBAND_USER_MEM */

#endif /* IB_UMEM_H */
