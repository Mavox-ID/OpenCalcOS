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
#ifndef _CRYPTO_SCATTERWALK_H
#define _CRYPTO_SCATTERWALK_H
#include <beep/mm.h>
#include <asm/scatterlist.h>

struct scatter_walk {
	struct scatterlist	*sg;
	struct page		*page;
	void			*data;
	unsigned int		len_this_page;
	unsigned int		len_this_segment;
	unsigned int		offset;
};

/* Define sg_next is an inline routine now in case we want to change
   scatterlist to a linked list later. */
static inline struct scatterlist *sg_next(struct scatterlist *sg)
{
	return sg + 1;
}

static inline int scatterwalk_samebuf(struct scatter_walk *walk_in,
				      struct scatter_walk *walk_out,
				      void *src_p, void *dst_p)
{
	return walk_in->page == walk_out->page &&
	       walk_in->offset == walk_out->offset &&
	       walk_in->data == src_p && walk_out->data == dst_p;
}

void *scatterwalk_whichbuf(struct scatter_walk *walk, unsigned int nbytes, void *scratch);
void scatterwalk_start(struct scatter_walk *walk, struct scatterlist *sg);
int scatterwalk_copychunks(void *buf, struct scatter_walk *walk, size_t nbytes, int out);
void scatterwalk_map(struct scatter_walk *walk, int out);
void scatterwalk_done(struct scatter_walk *walk, int out, int more);

#endif  /* _CRYPTO_SCATTERWALK_H */
