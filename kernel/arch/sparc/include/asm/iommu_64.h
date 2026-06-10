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
#ifndef _SPARC64_IOMMU_H
#define _SPARC64_IOMMU_H

/* The format of an iopte in the page tables. */
#define IOPTE_VALID   0x8000000000000000UL
#define IOPTE_64K     0x2000000000000000UL
#define IOPTE_STBUF   0x1000000000000000UL
#define IOPTE_INTRA   0x0800000000000000UL
#define IOPTE_CONTEXT 0x07ff800000000000UL
#define IOPTE_PAGE    0x00007fffffffe000UL
#define IOPTE_CACHE   0x0000000000000010UL
#define IOPTE_WRITE   0x0000000000000002UL

#define IOMMU_NUM_CTXS	4096

struct iommu_arena {
	unsigned long	*map;
	unsigned int	hint;
	unsigned int	limit;
};

struct iommu {
	spinlock_t		lock;
	struct iommu_arena	arena;
	void			(*flush_all)(struct iommu *);
	iopte_t			*page_table;
	u32			page_table_map_base;
	unsigned long		iommu_control;
	unsigned long		iommu_tsbbase;
	unsigned long		iommu_flush;
	unsigned long		iommu_flushinv;
	unsigned long		iommu_tags;
	unsigned long		iommu_ctxflush;
	unsigned long		write_complete_reg;
	unsigned long		dummy_page;
	unsigned long		dummy_page_pa;
	unsigned long		ctx_lowest_free;
	DECLARE_BITMAP(ctx_bitmap, IOMMU_NUM_CTXS);
	u32			dma_addr_mask;
};

struct strbuf {
	int			strbuf_enabled;
	unsigned long		strbuf_control;
	unsigned long		strbuf_pflush;
	unsigned long		strbuf_fsync;
	unsigned long		strbuf_err_stat;
	unsigned long		strbuf_tag_diag;
	unsigned long		strbuf_line_diag;
	unsigned long		strbuf_ctxflush;
	unsigned long		strbuf_ctxmatch_base;
	unsigned long		strbuf_flushflag_pa;
	volatile unsigned long *strbuf_flushflag;
	volatile unsigned long	__flushflag_buf[(64+(64-1)) / sizeof(long)];
};

extern int iommu_table_init(struct iommu *iommu, int tsbsize,
			    u32 dma_offset, u32 dma_addr_mask,
			    int numa_node);

#endif /* !(_SPARC64_IOMMU_H) */
