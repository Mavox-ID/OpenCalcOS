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
#include "testmode.h"
#include "debug.h"

#include <net/netlink.h>

enum ath6kl_tm_attr {
	__ATH6KL_TM_ATTR_INVALID	= 0,
	ATH6KL_TM_ATTR_CMD		= 1,
	ATH6KL_TM_ATTR_DATA		= 2,

	/* keep last */
	__ATH6KL_TM_ATTR_AFTER_LAST,
	ATH6KL_TM_ATTR_MAX		= __ATH6KL_TM_ATTR_AFTER_LAST - 1,
};

enum ath6kl_tm_cmd {
	ATH6KL_TM_CMD_TCMD		= 0,
	ATH6KL_TM_CMD_RX_REPORT		= 1,	/* not used anymore */
};

#define ATH6KL_TM_DATA_MAX_LEN		5000

static const struct nla_policy ath6kl_tm_policy[ATH6KL_TM_ATTR_MAX + 1] = {
	[ATH6KL_TM_ATTR_CMD]		= { .type = NLA_U32 },
	[ATH6KL_TM_ATTR_DATA]		= { .type = NLA_BINARY,
					    .len = ATH6KL_TM_DATA_MAX_LEN },
};

void ath6kl_tm_rx_event(struct ath6kl *ar, void *buf, size_t buf_len)
{
	struct sk_buff *skb;

	if (!buf || buf_len == 0)
		return;

	skb = cfg80211_testmode_alloc_event_skb(ar->wiphy, buf_len, GFP_KERNEL);
	if (!skb) {
		ath6kl_warn("failed to allocate testmode rx skb!\n");
		return;
	}
	if (nla_put_u32(skb, ATH6KL_TM_ATTR_CMD, ATH6KL_TM_CMD_TCMD) ||
	    nla_put(skb, ATH6KL_TM_ATTR_DATA, buf_len, buf))
		goto nla_put_failure;
	cfg80211_testmode_event(skb, GFP_KERNEL);
	return;

nla_put_failure:
	kfree_skb(skb);
	ath6kl_warn("nla_put failed on testmode rx skb!\n");
}

int ath6kl_tm_cmd(struct wiphy *wiphy, void *data, int len)
{
	struct ath6kl *ar = wiphy_priv(wiphy);
	struct nlattr *tb[ATH6KL_TM_ATTR_MAX + 1];
	int err, buf_len;
	void *buf;

	err = nla_parse(tb, ATH6KL_TM_ATTR_MAX, data, len,
			ath6kl_tm_policy);
	if (err)
		return err;

	if (!tb[ATH6KL_TM_ATTR_CMD])
		return -EINVAL;

	switch (nla_get_u32(tb[ATH6KL_TM_ATTR_CMD])) {
	case ATH6KL_TM_CMD_TCMD:
		if (!tb[ATH6KL_TM_ATTR_DATA])
			return -EINVAL;

		buf = nla_data(tb[ATH6KL_TM_ATTR_DATA]);
		buf_len = nla_len(tb[ATH6KL_TM_ATTR_DATA]);

		ath6kl_wmi_test_cmd(ar->wmi, buf, buf_len);

		return 0;

		break;
	case ATH6KL_TM_CMD_RX_REPORT:
	default:
		return -EOPNOTSUPP;
	}
}
