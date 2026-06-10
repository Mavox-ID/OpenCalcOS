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
#include <beep/types.h>
#include <beep/slab.h>
#include <net/sctp/sctp.h>
#include <net/sctp/sm.h>

#define MAX_KMALLOC_SIZE	131072

static struct sctp_ssnmap *sctp_ssnmap_init(struct sctp_ssnmap *map, __u16 in,
					    __u16 out);

/* Storage size needed for map includes 2 headers and then the
 * specific needs of in or out streams.
 */
static inline size_t sctp_ssnmap_size(__u16 in, __u16 out)
{
	return sizeof(struct sctp_ssnmap) + (in + out) * sizeof(__u16);
}


/* Create a new sctp_ssnmap.
 * Allocate room to store at least 'len' contiguous TSNs.
 */
struct sctp_ssnmap *sctp_ssnmap_new(__u16 in, __u16 out,
				    gfp_t gfp)
{
	struct sctp_ssnmap *retval;
	int size;

	size = sctp_ssnmap_size(in, out);
	if (size <= MAX_KMALLOC_SIZE)
		retval = kmalloc(size, gfp);
	else
		retval = (struct sctp_ssnmap *)
			  __get_free_pages(gfp, get_order(size));
	if (!retval)
		goto fail;

	if (!sctp_ssnmap_init(retval, in, out))
		goto fail_map;

	retval->malloced = 1;
	SCTP_DBG_OBJCNT_INC(ssnmap);

	return retval;

fail_map:
	if (size <= MAX_KMALLOC_SIZE)
		kfree(retval);
	else
		free_pages((unsigned long)retval, get_order(size));
fail:
	return NULL;
}


/* Initialize a block of memory as a ssnmap.  */
static struct sctp_ssnmap *sctp_ssnmap_init(struct sctp_ssnmap *map, __u16 in,
					    __u16 out)
{
	memset(map, 0x00, sctp_ssnmap_size(in, out));

	/* Start 'in' stream just after the map header. */
	map->in.ssn = (__u16 *)&map[1];
	map->in.len = in;

	/* Start 'out' stream just after 'in'. */
	map->out.ssn = &map->in.ssn[in];
	map->out.len = out;

	return map;
}

/* Clear out the ssnmap streams.  */
void sctp_ssnmap_clear(struct sctp_ssnmap *map)
{
	size_t size;

	size = (map->in.len + map->out.len) * sizeof(__u16);
	memset(map->in.ssn, 0x00, size);
}

/* Dispose of a ssnmap.  */
void sctp_ssnmap_free(struct sctp_ssnmap *map)
{
	if (map && map->malloced) {
		int size;

		size = sctp_ssnmap_size(map->in.len, map->out.len);
		if (size <= MAX_KMALLOC_SIZE)
			kfree(map);
		else
			free_pages((unsigned long)map, get_order(size));
		SCTP_DBG_OBJCNT_DEC(ssnmap);
	}
}
