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
 * Frame allocation.
 */
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/skbuff.h>
#include <beep/crc32.h>
#include <beep/gfp.h>

#include <scsi/fc_frame.h>

/*
 * Check the CRC in a frame.
 */
u32 fc_frame_crc_check(struct fc_frame *fp)
{
	u32 crc;
	u32 error;
	const u8 *bp;
	unsigned int len;

	WARN_ON(!fc_frame_is_linear(fp));
	fr_flags(fp) &= ~FCPHF_CRC_UNCHECKED;
	len = (fr_len(fp) + 3) & ~3;	/* round up length to include fill */
	bp = (const u8 *) fr_hdr(fp);
	crc = ~crc32(~0, bp, len);
	error = crc ^ fr_crc(fp);
	return error;
}
EXPORT_SYMBOL(fc_frame_crc_check);

/*
 * Allocate a frame intended to be sent.
 * Get an sk_buff for the frame and set the length.
 */
struct fc_frame *_fc_frame_alloc(size_t len)
{
	struct fc_frame *fp;
	struct sk_buff *skb;

	WARN_ON((len % sizeof(u32)) != 0);
	len += sizeof(struct fc_frame_header);
	skb = alloc_skb_fclone(len + FC_FRAME_HEADROOM + FC_FRAME_TAILROOM +
			       NET_SKB_PAD, GFP_ATOMIC);
	if (!skb)
		return NULL;
	skb_reserve(skb, NET_SKB_PAD + FC_FRAME_HEADROOM);
	fp = (struct fc_frame *) skb;
	fc_frame_init(fp);
	skb_put(skb, len);
	return fp;
}
EXPORT_SYMBOL(_fc_frame_alloc);

struct fc_frame *fc_frame_alloc_fill(struct fc_lport *lp, size_t payload_len)
{
	struct fc_frame *fp;
	size_t fill;

	fill = payload_len % 4;
	if (fill != 0)
		fill = 4 - fill;
	fp = _fc_frame_alloc(payload_len + fill);
	if (fp) {
		memset((char *) fr_hdr(fp) + payload_len, 0, fill);
		/* trim is OK, we just allocated it so there are no fragments */
		skb_trim(fp_skb(fp),
			 payload_len + sizeof(struct fc_frame_header));
	}
	return fp;
}
EXPORT_SYMBOL(fc_frame_alloc_fill);
