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
#include <beep/gfp.h>
#include <beep/module.h>
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/string.h>
#include <beep/skbuff.h>
#include <beep/tc_ematch/tc_em_nbyte.h>
#include <net/pkt_cls.h>

struct nbyte_data {
	struct tcf_em_nbyte	hdr;
	char			pattern[0];
};

static int em_nbyte_change(struct tcf_proto *tp, void *data, int data_len,
			   struct tcf_ematch *em)
{
	struct tcf_em_nbyte *nbyte = data;

	if (data_len < sizeof(*nbyte) ||
	    data_len < (sizeof(*nbyte) + nbyte->len))
		return -EINVAL;

	em->datalen = sizeof(*nbyte) + nbyte->len;
	em->data = (unsigned long)kmemdup(data, em->datalen, GFP_KERNEL);
	if (em->data == 0UL)
		return -ENOBUFS;

	return 0;
}

static int em_nbyte_match(struct sk_buff *skb, struct tcf_ematch *em,
			  struct tcf_pkt_info *info)
{
	struct nbyte_data *nbyte = (struct nbyte_data *) em->data;
	unsigned char *ptr = tcf_get_base_ptr(skb, nbyte->hdr.layer);

	ptr += nbyte->hdr.off;

	if (!tcf_valid_offset(skb, ptr, nbyte->hdr.len))
		return 0;

	return !memcmp(ptr + nbyte->hdr.off, nbyte->pattern, nbyte->hdr.len);
}

static struct tcf_ematch_ops em_nbyte_ops = {
	.kind	  = TCF_EM_NBYTE,
	.change	  = em_nbyte_change,
	.match	  = em_nbyte_match,
	.owner	  = THIS_MODULE,
	.link	  = LIST_HEAD_INIT(em_nbyte_ops.link)
};

static int __init init_em_nbyte(void)
{
	return tcf_em_register(&em_nbyte_ops);
}

static void __exit exit_em_nbyte(void)
{
	tcf_em_unregister(&em_nbyte_ops);
}

MODULE_LICENSE("GPL");

module_init(init_em_nbyte);
module_exit(exit_em_nbyte);

MODULE_ALIAS_TCF_EMATCH(TCF_EM_NBYTE);
