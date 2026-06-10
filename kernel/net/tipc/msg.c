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
#include "core.h"
#include "msg.h"

u32 tipc_msg_tot_importance(struct tipc_msg *m)
{
	if (likely(msg_isdata(m))) {
		if (likely(msg_orignode(m) == tipc_own_addr))
			return msg_importance(m);
		return msg_importance(m) + 4;
	}
	if ((msg_user(m) == MSG_FRAGMENTER)  &&
	    (msg_type(m) == FIRST_FRAGMENT))
		return msg_importance(msg_get_wrapped(m));
	return msg_importance(m);
}


void tipc_msg_init(struct tipc_msg *m, u32 user, u32 type,
			    u32 hsize, u32 destnode)
{
	memset(m, 0, hsize);
	msg_set_version(m);
	msg_set_user(m, user);
	msg_set_hdr_sz(m, hsize);
	msg_set_size(m, hsize);
	msg_set_prevnode(m, tipc_own_addr);
	msg_set_type(m, type);
	msg_set_orignode(m, tipc_own_addr);
	msg_set_destnode(m, destnode);
}

/**
 * tipc_msg_build - create message using specified header and data
 *
 * Note: Caller must not hold any locks in case copy_from_user() is interrupted!
 *
 * Returns message data size or errno
 */
int tipc_msg_build(struct tipc_msg *hdr, struct iovec const *msg_sect,
		   u32 num_sect, unsigned int total_len,
			    int max_size, int usrmem, struct sk_buff **buf)
{
	int dsz, sz, hsz, pos, res, cnt;

	dsz = total_len;
	pos = hsz = msg_hdr_sz(hdr);
	sz = hsz + dsz;
	msg_set_size(hdr, sz);
	if (unlikely(sz > max_size)) {
		*buf = NULL;
		return dsz;
	}

	*buf = tipc_buf_acquire(sz);
	if (!(*buf))
		return -ENOMEM;
	skb_copy_to_linear_data(*buf, hdr, hsz);
	for (res = 1, cnt = 0; res && (cnt < num_sect); cnt++) {
		if (likely(usrmem))
			res = !copy_from_user((*buf)->data + pos,
					      msg_sect[cnt].iov_base,
					      msg_sect[cnt].iov_len);
		else
			skb_copy_to_linear_data_offset(*buf, pos,
						       msg_sect[cnt].iov_base,
						       msg_sect[cnt].iov_len);
		pos += msg_sect[cnt].iov_len;
	}
	if (likely(res))
		return dsz;

	kfree_skb(*buf);
	*buf = NULL;
	return -EFAULT;
}
