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
#ifndef IEEE_802154_LOCAL_H
#define IEEE_802154_LOCAL_H

int __init ieee802154_nl_init(void);
void __exit ieee802154_nl_exit(void);

#define IEEE802154_OP(_cmd, _func)			\
	{						\
		.cmd	= _cmd,				\
		.policy	= ieee802154_policy,		\
		.doit	= _func,			\
		.dumpit	= NULL,				\
		.flags	= GENL_ADMIN_PERM,		\
	}

#define IEEE802154_DUMP(_cmd, _func, _dump)		\
	{						\
		.cmd	= _cmd,				\
		.policy	= ieee802154_policy,		\
		.doit	= _func,			\
		.dumpit	= _dump,			\
	}

struct genl_info;

struct sk_buff *ieee802154_nl_create(int flags, u8 req);
int ieee802154_nl_mcast(struct sk_buff *msg, unsigned int group);
struct sk_buff *ieee802154_nl_new_reply(struct genl_info *info,
		int flags, u8 req);
int ieee802154_nl_reply(struct sk_buff *msg, struct genl_info *info);

extern struct genl_family nl802154_family;
int nl802154_mac_register(void);
int nl802154_phy_register(void);

#endif
